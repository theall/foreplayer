#include "transparentmenu.h"

TTransparentMenu::TTransparentMenu(QWidget *parent) :
    TAbstractMenu(parent),
    mLastActivedAction(NULL)
{
    mActionDisable = new QAction(this);
    mActionTransparent1 = new QAction(this);
    mActionTransparent2 = new QAction(this);
    mActionTransparent3 = new QAction(this);
    mActionTransparent4 = new QAction(this);
    mActionTransparent5 = new QAction(this);
    mActionTransparent6 = new QAction(this);
    mActionTransparent7 = new QAction(this);
    mActionTransparent8 = new QAction(this);
    mActionTransparent9 = new QAction(this);
    mActionTransparent10 = new QAction(this);
    mActionDisableWhileActived = new QAction(this);

    connect(mActionDisable, SIGNAL(triggered(bool)), this, SLOT(slotActionTriggered(bool)));
    connect(mActionTransparent1, SIGNAL(triggered(bool)), this, SLOT(slotActionTriggered(bool)));
    connect(mActionTransparent2, SIGNAL(triggered(bool)), this, SLOT(slotActionTriggered(bool)));
    connect(mActionTransparent3, SIGNAL(triggered(bool)), this, SLOT(slotActionTriggered(bool)));
    connect(mActionTransparent4, SIGNAL(triggered(bool)), this, SLOT(slotActionTriggered(bool)));
    connect(mActionTransparent5, SIGNAL(triggered(bool)), this, SLOT(slotActionTriggered(bool)));
    connect(mActionTransparent6, SIGNAL(triggered(bool)), this, SLOT(slotActionTriggered(bool)));
    connect(mActionTransparent7, SIGNAL(triggered(bool)), this, SLOT(slotActionTriggered(bool)));
    connect(mActionTransparent8, SIGNAL(triggered(bool)), this, SLOT(slotActionTriggered(bool)));
    connect(mActionTransparent9, SIGNAL(triggered(bool)), this, SLOT(slotActionTriggered(bool)));
    connect(mActionTransparent10, SIGNAL(triggered(bool)), this, SLOT(slotActionTriggered(bool)));
    connect(mActionDisableWhileActived, SIGNAL(triggered(bool)), this, SLOT(slotActionTriggered(bool)));

    addAction(mActionDisable);
    addAction(mActionTransparent1);
    addAction(mActionTransparent2);
    addAction(mActionTransparent3);
    addAction(mActionTransparent4);
    addAction(mActionTransparent5);
    addAction(mActionTransparent6);
    addAction(mActionTransparent7);
    addAction(mActionTransparent8);
    addAction(mActionTransparent9);
    addAction(mActionTransparent10);
    addSeparator();
    addAction(mActionDisableWhileActived);

    retranslateUi();
}

void TTransparentMenu::slotActionTriggered(bool)
{
    QAction *action = static_cast<QAction*>(sender());
    if(action)
    {
        if(action != mActionDisableWhileActived && mLastActivedAction)
        {
            mLastActivedAction->setChecked(false);
        }

        if(action == mActionDisable)
        {
            emit onOpacityChanged(1.0);
        }
        else if(action == mActionTransparent1)
        {
            emit onOpacityChanged(0.9);
        }
        else if(action == mActionTransparent2)
        {
            emit onOpacityChanged(0.8);
        }
        else if(action == mActionTransparent3)
        {
            emit onOpacityChanged(0.7);
        }
        else if(action == mActionTransparent4)
        {
            emit onOpacityChanged(0.6);
        }
        else if(action == mActionTransparent5)
        {
            emit onOpacityChanged(0.5);
        }
        else if(action == mActionTransparent6)
        {
            emit onOpacityChanged(0.4);
        }
        else if(action == mActionTransparent7)
        {
            emit onOpacityChanged(0.3);
        }
        else if(action == mActionTransparent8)
        {
            emit onOpacityChanged(0.2);
        }
        else if(action == mActionTransparent9)
        {
            emit onOpacityChanged(0.1);
        }
        else if(action == mActionTransparent10)
        {
            emit onOpacityChanged(0.0);
        }
        else if(action == mActionDisableWhileActived)
        {
            emit onOpacityChanged(0.0);
        }
    }
    mLastActivedAction = action;
}

void TTransparentMenu::retranslateUi()
{
    mActionDisable->setText(tr("Opacity"));
    mActionTransparent1->setText(tr("10% Transparent"));
    mActionTransparent2->setText(tr("20% Transparent"));
    mActionTransparent3->setText(tr("30% Transparent"));
    mActionTransparent4->setText(tr("40% Transparent"));
    mActionTransparent5->setText(tr("50% Transparent"));
    mActionTransparent6->setText(tr("60% Transparent"));
    mActionTransparent7->setText(tr("70% Transparent"));
    mActionTransparent8->setText(tr("80% Transparent"));
    mActionTransparent9->setText(tr("90% Transparent"));
    mActionTransparent10->setText(tr("100% Transparent"));
    mActionDisableWhileActived->setText(tr("Opacity While Actived"));
}