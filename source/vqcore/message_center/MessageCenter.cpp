
#include "MessageCenter.h"

namespace Vam {

void MessageCenter::subscribe( const std::string &messageType,
                               IMessageClient *sub )
{
    if( sub != nullptr ) {
        m_lock.lockForWrite();
        m_subscribers.insert( messageType, sub );
        m_clients.insert( sub->messageClientId(), sub );
    }
}


void MessageCenter::subscribe( const std::stringList &messageTypes,
                               IMessageClient *sub )
{
    if( sub != nullptr ) {
        m_lock.lockForWrite();
        for( const std::string &msgType : messageTypes ) {
            m_subscribers.insert( msgType, sub );
            m_clients.insert( sub->messageClientId(), sub );
        }
    }
}


void MessageCenter::removeSubscriber( IMessageClient *client )
{
    if( client != nullptr ) {
        m_lock.lockForWrite();
        for( std::string &mtype : m_subscribers.keys() ) {
            m_subscribers.remove( mtype, client );
        }
        m_clients.remove( client->messageClientId() );
    }
}


void MessageCenter::removeSubscriber( const std::string &clientId )
{
    m_lock.lockForWrite();
    IMessageClient *client = m_clients.value( clientId );
    removeSubscriber( client );
}


void MessageCenter::notify( const IMessageClient *originator,
                            const std::string &messageType,
                            const Parameters &params )
{
    m_lock.lockForRead();
    QList< IMessageClient * > clients = m_subscribers.values( messageType );
    for( IMessageClient *client : clients ) {
        client->onMessage( originator, messageType, params );
    }
}

}
