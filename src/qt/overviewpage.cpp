// Copyright (c) 2011-2018 The Bitcoin Core developers
// Copyright (c) 2019-2020 The NutuCoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <qt/overviewpage.h>
#include <qt/forms/ui_overviewpage.h>

#include <qt/bitcoinunits.h>
#include <qt/clientmodel.h>
#include <qt/guiconstants.h>
#include <qt/guiutil.h>
#include <qt/optionsmodel.h>
#include <qt/platformstyle.h>
#include <qt/transactionfilterproxy.h>
#include <qt/transactiontablemodel.h>
#include <qt/walletmodel.h>
#include <qt/walletframe.h>

#include <QAbstractItemDelegate>
#include <QAction>
#include <QDesktopWidget>
#include <QPainter>
#include <QHelpEvent>

#define DECORATION_SIZE 54
#define ICON_SIZE_WIDTH 35
#define ICON_SIZE_HEIGHT 40
#define HEADER_HEIGHT 30
#define NUM_ITEMS 6

#define DATE_MARGIN 20
#define TYPE_MARGIN 140
#define ADDRESS_MARGIN 200
#define RIGHT_MARGIN 120

Q_DECLARE_METATYPE(interfaces::WalletBalances)

extern WalletFrame* gWalletFrame;
extern QAction* gHistoryAction;

class TxViewDelegate : public QAbstractItemDelegate
{
    Q_OBJECT
public:
    explicit TxViewDelegate(const PlatformStyle *_platformStyle, QObject *parent=nullptr):
        QAbstractItemDelegate(parent), unit(BitcoinUnits::BTC),
        platformStyle(_platformStyle)
    {

    }

    bool helpEvent (QHelpEvent* event, QAbstractItemView* view, const QStyleOptionViewItem& option,
                                            const QModelIndex& index)
    {
        if( !event || !view )
            return false;

        if( event->type() == QEvent::ToolTip )
        {
            if (index.row() == 0)
                return true;

            const QModelIndex index1 = index.sibling(index.row() - 1, index.column());
            return QAbstractItemDelegate::helpEvent(event, view, option, index1);
        }

        return QAbstractItemDelegate::helpEvent(event, view, option, index);
    }

    inline void paint(QPainter *painter, const QStyleOptionViewItem &option,
                      const QModelIndex &index ) const
    {
        painter->save();

        QRect mainRect = option.rect;
        int width = mainRect.width();
        int addressWidth = width - RIGHT_MARGIN - ADDRESS_MARGIN;

        if (index.row() == 0)
        {
            painter->setBrush(QBrush(QColor(0,0,0)));
            painter->fillRect(mainRect, painter->brush());

            QRect dateRect(mainRect.left() + DATE_MARGIN, mainRect.top(), 30, HEADER_HEIGHT);

            painter->setPen(QColor(255,255,255));
            painter->drawText(dateRect, Qt::AlignLeft|Qt::AlignVCenter, "Date");

            QRect typeRect(mainRect.left() + TYPE_MARGIN, mainRect.top(), 30, HEADER_HEIGHT);
            painter->drawText(typeRect, Qt::AlignLeft|Qt::AlignVCenter, "Type");

            QRect addressRect(mainRect.left() + ADDRESS_MARGIN, mainRect.top(), addressWidth, HEADER_HEIGHT);
            painter->drawText(addressRect, Qt::AlignLeft|Qt::AlignVCenter, "Address");

            QRect NTURect(width - RIGHT_MARGIN, mainRect.top(), RIGHT_MARGIN, HEADER_HEIGHT);
            painter->drawText(NTURect, Qt::AlignLeft|Qt::AlignVCenter, "Amount");
            return;
        }


        if((index.row() % 2) == 1)
        {
            painter->setBrush(QBrush(QColor(230,231,232)));
            painter->fillRect(mainRect, painter->brush());
        }


        const QModelIndex index1 = index.sibling(index.row() - 1, index.column());

        QIcon icon = qvariant_cast<QIcon>(index1.data(TransactionTableModel::RawDecorationRole));
        QDateTime date = index1.data(TransactionTableModel::DateRole).toDateTime();
        QString address = index1.data(Qt::DisplayRole).toString();
        if (addressWidth < 100)
        {
          if (address.length() > 8)
          {
            address = address.mid(0,5);
            address.append("...");
          }
        }
        else if (addressWidth < 140)
        {
          if (address.length() > 12)
          {
            address = address.mid(0,9);
            address.append("...");
          }
        }
        else if (addressWidth < 170)
        {
          if (address.length() > 16)
          {
            address = address.mid(0,13);
            address.append("...");
          }
        }
        else if (addressWidth < 210)
        {
          if (address.length() > 22)
          {
            address = address.mid(0,19);
            address.append("...");
          }
        }
        else if (addressWidth < 250)
        {
          if (address.length() > 28)
          {
            address = address.mid(0,25);
            address.append("...");
          }
        }

        qint64 amount = index1.data(TransactionTableModel::AmountRole).toLongLong();
        bool confirmed = index1.data(TransactionTableModel::ConfirmedRole).toBool();
        QVariant value = index1.data(Qt::ForegroundRole);

        QColor foreground = option.palette.color(QPalette::Text);
        if(value.canConvert<QBrush>())
        {
            QBrush brush = qvariant_cast<QBrush>(value);
            foreground = brush.color();
        }

        painter->setPen(foreground);

        if(amount < 0)
        {
            foreground = COLOR_NEGATIVE;
        }
        else if(!confirmed)
        {
            foreground = COLOR_UNCONFIRMED;
        }
        else
        {
            foreground = option.palette.color(QPalette::Text);
        }

        QString amountText = BitcoinUnits::formatWithUnit(unit, amount, true, BitcoinUnits::separatorAlways);
        if(!confirmed)
        {
            amountText = QString("[") + amountText + QString("]");
        }

        QRect dateRect(mainRect.left() + DATE_MARGIN, mainRect.top(), 100, mainRect.height());
        painter->setPen(foreground);
        painter->drawText(dateRect, Qt::AlignLeft|Qt::AlignVCenter, GUIUtil::dateTimeStr(date));

        QRect decorationRect(mainRect.left() + TYPE_MARGIN, mainRect.top() + 8, ICON_SIZE_WIDTH, ICON_SIZE_HEIGHT);
        icon.paint(painter, decorationRect);

        QRect addressRect(mainRect.left() + ADDRESS_MARGIN, mainRect.top(), 2 * width - RIGHT_MARGIN - ADDRESS_MARGIN - DATE_MARGIN, mainRect.height());
        painter->drawText(addressRect, Qt::AlignLeft|Qt::AlignVCenter, address);

        QRect NTURect(width - RIGHT_MARGIN, mainRect.top(), RIGHT_MARGIN, mainRect.height());
        painter->drawText(NTURect, Qt::AlignLeft|Qt::AlignVCenter, amountText);

        painter->restore();
    }

    inline QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        if (index.row() == 0)
        {
            return QSize(HEADER_HEIGHT, HEADER_HEIGHT);
        }
        return QSize(DECORATION_SIZE, DECORATION_SIZE);
    }

    int unit;
    const PlatformStyle *platformStyle;

};
#include <qt/overviewpage.moc>

OverviewPage::OverviewPage(const PlatformStyle *platformStyle, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OverviewPage),
    clientModel(0),
    walletModel(0),
    txdelegate(new TxViewDelegate(platformStyle, this))
{
    ui->setupUi(this);

    m_balances.balance = -1;

    // use a SingleColorIcon for the "out of sync warning" icon
    QIcon icon = QIcon(":/icons/warning");

    ui->labelTransactionsStatus->setIcon(icon);
    QString styleSheet = ".QPushButton { background-color: transparent;"
                         "border: none;"
                         "qproperty-text: \"\" }";
    ui->labelTransactionsStatus->setStyleSheet(styleSheet);
    ui->labelWalletStatus->setStyleSheet(styleSheet);
    ui->labelWalletStatus->setIcon(icon);
    ui->labelOutOfSync->setStyleSheet(QString("QLabel {color:#f7410d ;font-weight:bold}"));

    QRect rec = QApplication::desktop()->screenGeometry();

    int screenHeight = rec.height();
    int screenWidth = rec.width();

    int width = 400;
    int height = 100;

    double ratioWidth = static_cast <double> (screenWidth)/1920;
    double ratioHeight = static_cast <double> (screenHeight)/1080;

    width = static_cast <int>( width * ratioWidth);
    height = static_cast <int>(height * ratioHeight);

    ui->logo->setIcon(QIcon(":/icons/logo").pixmap(width, height));
    ui->logo->resize(width, height);
    ui->verticalSpacer_3->changeSize(0, static_cast <int>( 10 * ratioHeight));

    // Recent transactions
    ui->listTransactions->setItemDelegate(txdelegate);
    ui->listTransactions->setIconSize(QSize(DECORATION_SIZE, DECORATION_SIZE));
    ui->listTransactions->setMinimumHeight(NUM_ITEMS * (DECORATION_SIZE + 2));
    ui->listTransactions->setAttribute(Qt::WA_MacShowFocusRect, false);

    connect(ui->listTransactions, SIGNAL(clicked(QModelIndex)), this, SLOT(handleTransactionClicked(QModelIndex)));
    connect(ui->btnShowAll, SIGNAL(clicked()), this, SLOT(handleShowAllClicked()));

    // start with displaying the "out of sync" warnings
    showOutOfSyncWarning(true);
    connect(ui->labelWalletStatus, SIGNAL(clicked()), this, SLOT(handleOutOfSyncWarningClicks()));
    connect(ui->labelTransactionsStatus, SIGNAL(clicked()), this, SLOT(handleOutOfSyncWarningClicks()));
}

void OverviewPage::handleTransactionClicked(const QModelIndex &index)
{
    if(filter)
    {
        if (index.row() == 0)
            return;

        const QModelIndex &index1 = index.sibling(index.row() - 1, index.column());
        Q_EMIT transactionClicked(filter->mapToSource(index1));
    }
}

void OverviewPage::handleShowAllClicked()
{
    if (gHistoryAction) gHistoryAction->setChecked(true);
    if (gWalletFrame) gWalletFrame->gotoHistoryPage();
}

void OverviewPage::handleOutOfSyncWarningClicks()
{
    Q_EMIT outOfSyncWarningClicked();
}

OverviewPage::~OverviewPage()
{
    delete ui;
}

void OverviewPage::setBalance(const interfaces::WalletBalances& balances)
{
    int unit = walletModel->getOptionsModel()->getDisplayUnit();
    m_balances = balances;
    ui->labelBalance->setText(BitcoinUnits::formatWithUnit(unit, balances.balance, false, BitcoinUnits::separatorAlways));
    ui->labelUnconfirmed->setText(BitcoinUnits::formatWithUnit(unit, balances.unconfirmed_balance, false, BitcoinUnits::separatorAlways));
    ui->labelImmature->setText(BitcoinUnits::formatWithUnit(unit, balances.immature_balance, false, BitcoinUnits::separatorAlways));
    ui->labelTotal->setText(BitcoinUnits::formatWithUnit(unit, balances.balance + balances.unconfirmed_balance + balances.immature_balance, false, BitcoinUnits::separatorAlways));
    ui->labelWatchAvailable->setText(BitcoinUnits::formatWithUnit(unit, balances.watch_only_balance, false, BitcoinUnits::separatorAlways));
    ui->labelWatchPending->setText(BitcoinUnits::formatWithUnit(unit, balances.unconfirmed_watch_only_balance, false, BitcoinUnits::separatorAlways));
    ui->labelWatchImmature->setText(BitcoinUnits::formatWithUnit(unit, balances.immature_watch_only_balance, false, BitcoinUnits::separatorAlways));
    ui->labelWatchTotal->setText(BitcoinUnits::formatWithUnit(unit, balances.watch_only_balance + balances.unconfirmed_watch_only_balance + balances.immature_watch_only_balance, false, BitcoinUnits::separatorAlways));

    // only show immature (newly mined) balance if it's non-zero, so as not to complicate things
    // for the non-mining users
    bool showWatchOnlyImmature = balances.immature_watch_only_balance != 0;

    // for symmetry reasons also show immature label when the watch-only one is shown
    ui->labelWatchImmature->setVisible(showWatchOnlyImmature); // show watch-only immature balance
}

// show/hide watch-only labels
void OverviewPage::updateWatchOnlyLabels(bool showWatchOnly)
{
    ui->labelSpendable->setVisible(showWatchOnly);      // show spendable label (only when watch-only is active)
    ui->labelWatchonly->setVisible(showWatchOnly);      // show watch-only label
    ui->lineWatchBalance->setVisible(showWatchOnly);    // show watch-only balance separator line
    ui->labelWatchAvailable->setVisible(showWatchOnly); // show watch-only available balance
    ui->labelWatchPending->setVisible(showWatchOnly);   // show watch-only pending balance
    ui->labelWatchTotal->setVisible(showWatchOnly);     // show watch-only total balance

    if (!showWatchOnly)
        ui->labelWatchImmature->hide();
}

void OverviewPage::setClientModel(ClientModel *model)
{
    this->clientModel = model;
    if(model)
    {
        // Show warning if this is a prerelease version
        connect(model, SIGNAL(alertsChanged(QString)), this, SLOT(updateAlerts(QString)));
        updateAlerts(model->getStatusBarWarnings());
    }
}

void OverviewPage::setWalletModel(WalletModel *model)
{
    this->walletModel = model;
    if(model && model->getOptionsModel())
    {
        // Set up transaction list
        filter.reset(new TransactionFilterProxy());
        filter->setSourceModel(model->getTransactionTableModel());
        filter->setLimit(NUM_ITEMS);
        filter->setDynamicSortFilter(true);
        filter->setSortRole(Qt::EditRole);
        filter->setShowInactive(false);
        filter->sort(TransactionTableModel::Date, Qt::DescendingOrder);

        ui->listTransactions->setModel(filter.get());
        ui->listTransactions->setModelColumn(TransactionTableModel::ToAddress);

        // Keep up to date with wallet
        interfaces::Wallet& wallet = model->wallet();
        interfaces::WalletBalances balances = wallet.getBalances();
        setBalance(balances);
        connect(model, SIGNAL(balanceChanged(interfaces::WalletBalances)), this, SLOT(setBalance(interfaces::WalletBalances)));

        connect(model->getOptionsModel(), SIGNAL(displayUnitChanged(int)), this, SLOT(updateDisplayUnit()));

        updateWatchOnlyLabels(wallet.haveWatchOnly());
        connect(model, SIGNAL(notifyWatchonlyChanged(bool)), this, SLOT(updateWatchOnlyLabels(bool)));
    }

    // update the display unit, to not use the default ("BTC")
    updateDisplayUnit();
}

void OverviewPage::updateDisplayUnit()
{
    if(walletModel && walletModel->getOptionsModel())
    {
        if (m_balances.balance != -1) {
            setBalance(m_balances);
        }

        // Update txdelegate->unit with the current unit
        txdelegate->unit = walletModel->getOptionsModel()->getDisplayUnit();

        ui->listTransactions->update();
    }
}

void OverviewPage::updateAlerts(const QString &warnings)
{
    this->ui->labelAlerts->setVisible(!warnings.isEmpty());
    this->ui->labelAlerts->setText(warnings);
}

void OverviewPage::showOutOfSyncWarning(bool fShow)
{
    ui->labelWalletStatus->setVisible(fShow);
    ui->labelOutOfSync->setVisible(fShow);
    ui->labelOutOfSync_2->setVisible(fShow);
    ui->labelTransactionsStatus->setVisible(fShow);
}
