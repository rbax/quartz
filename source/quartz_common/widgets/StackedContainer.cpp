
#include "StackedContainer.h"

namespace Vam { namespace Quartz {

StackedContainer::StackedContainer( int selectorDimention,
                                    Qt::Orientation orientation,
                                    QWidget *parent = nullptr )
    : QWidget( parent )
    , m_selector( new QzScroller( orientation,
                                  selectorDimention,
                                  selectorDimention,
                                  this ))
    , m_stackWidget( new QStackedWidget( this ))
{
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget( m_selector );
    layout->addWidget( m_stackWidget );
    layout->setContentsMargins( QMargins() );
    m_selector->setContentsMargins( QMargins() );
    m_stackWidget->setContentsMargins( QMargins() );
    this->setLayout( layout );
}

QWidget * StackedContainer::widget( const QString &id ) const
{
//    QWidget *widget = m_widgets.value( id );
//    return widget;
    QWidget *widget = nullptr;
    Item::Ptr item = m_items.value( id );
    if( item ) {
        widget = item->m_widget;
    }
    return widget;
}


QString StackedContainer::currentId() const
{
    return m_selectedId;
}


QList< QString > StackedContainer::allIds() const
{
    return m_items.keys();
}


void StackedContainer::addWidget( const QString &id,
                                  const QString &displayName,
                                  QWidget *widget )
{
    if( widget != nullptr ) {
        IdButton *btn = new IdButton( id, displayName, this );
        int index = m_stackWidget->addWidget( widget );
        Item::Ptr item = Item::create( index, btn, widget );
        m_items.insert( id, item );
        m_selectedId = id;
        m_stackWidget->setCurrentIndex( index );
        m_selector->addWidget( widget );
    }
}


void StackedContainer::removeWidget( QString id )
{
    Item::Ptr item = m_items.value( id );
    if( item ) {
        m_selector->removeWidget( item->m_btn );
        m_stackWidget->removeWidget( item->m_widget );
        m_items.remove( id );
        updateIndeces();
    }
}


void StackedContainer::removeWidget( QWidget widget )
{
    for( auto it = m_items.begin(); it != m_items.end(); ++ it ) {
        Item::Ptr item = it.value();
        if( item->m_widget == widget ) {
            removeWidget( it.key() );
            /* I am not breaking here because same widget might have been added
             * multiple times. If later if we find it not important we can break
             * here.
             */
        }
    }
}


void StackedContainer::select( QString id )
{
    Item::Ptr item = m_items.value( id );
    if( item ) {
        m_stackWidget->setCurrentIndex( item->m_index );
    }
}


void StackedContainer::updateIndeces()
{
    for( int i = 0; i < m_stackWidget->count() && i < m_items.size() ; ++ i ) {
        QWidget *widget = m_stackWidget->widget( i );
    }
}

} }