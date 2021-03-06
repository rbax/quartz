#include <QPushButton>
#include <QHBoxLayout>
#include <QStyle>

#include "TitleBar.h"

namespace Vam { namespace Quartz {


TitleBar::TitleBar( int height, QWidget *parent )
    : QWidget( parent )
    , m_height( height )

{
    QPixmap clspx = style()->standardPixmap( QStyle::SP_TitleBarCloseButton );
    QPixmap maxpx = style()->standardPixmap( QStyle::SP_TitleBarMaxButton );
    QPixmap minpx = style()->standardPixmap( QStyle::SP_TitleBarMinButton );


    m_scroller = new QzScroller( Qt::Horizontal, height, height, this );
    m_minimizeBtn = new QPushButton( this );
    m_maxRestoreBtn = new QPushButton( this );
    m_closeBtn = new QPushButton( this );
    m_closeBtn->setIcon( clspx );
    m_minimizeBtn->setIcon( minpx );
    m_maxRestoreBtn->setIcon( maxpx );

    m_scroller->setContentsMargins( QMargins() );
    QHBoxLayout *layout = new QHBoxLayout();
    layout->setContentsMargins( QMargins() );
    layout->addStretch();
    layout->addWidget( m_minimizeBtn );
    layout->addWidget( m_maxRestoreBtn );
    layout->addWidget( m_closeBtn );
    m_minimizeBtn->setMaximumSize( 20, 20 );
    m_maxRestoreBtn->setMaximumSize( 20, 20 );
    m_closeBtn->setMaximumSize( 20, 20 );
    m_minimizeBtn->setMinimumSize( 20, 20 );
    m_maxRestoreBtn->setMinimumSize( 20, 20 );
    m_closeBtn->setMinimumSize( 20, 20 );
    this->setContentsMargins( QMargins( 0, 0, 3, 0 ));
    this->setLayout( layout );
    setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Fixed );

    connect( m_closeBtn,
             SIGNAL( clicked( bool )),
             this,
             SIGNAL( sigCloseRequested() ));
    connect( m_maxRestoreBtn,
             SIGNAL( clicked( bool )),
             this,
             SIGNAL( sigMaxRestoreRequested() ));
    connect( m_minimizeBtn,
             SIGNAL( clicked( bool )),
             this,
             SIGNAL( sigMinimizeRequested() ));


}

void TitleBar::addItem( QuartzItem *item )
{
    if( item != nullptr ) {
        m_items.insert( item->itemId(), item );
        m_scroller->addWidget( item );
    }
}


void TitleBar::removeItem( QuartzItem *item )
{
    if( item != nullptr && m_items.contains( item->itemId() )) {
        m_items.remove( item->itemId() );
        m_scroller->removeWidget( item );
        delete item;
    }
}


void TitleBar::removeItem( const QString &itemId )
{
    QuartzItem *item = m_items.value( itemId );
    if( item != nullptr ) {
        m_items.remove( itemId );
        m_scroller->removeWidget( item );
        delete item;
    }
}


QList< QuartzItem * > TitleBar::items() const
{
    return m_items.values();
}


QList< QuartzItem * > TitleBar::items( const QString category )
{
    QList< QuartzItem *> filteredItems;
    for( QuartzItem *item : m_items.values() ) {
        if( item->itemCategory() == category ) {
            filteredItems.append( item );
        }
    }
    return filteredItems;
}


void TitleBar::removeCategory( const QString &category )
{
    QList< QuartzItem * > itemList = items( category );
    for( QuartzItem *item : itemList ) {
        removeItem( item );
    }
}


void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit sigMaxRestoreRequested();
}

} }
