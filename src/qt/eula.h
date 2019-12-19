// Copyright (c) 2019 The NutuCoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef BITCOIN_QT_EULA_H
#define BITCOIN_QT_EULA_H

#include <QThread>
#include <QDialog>
#include <tinyformat.h>


namespace Ui {
class Eula;
}

class Eula : public QDialog
{
  Q_OBJECT

public:
    explicit Eula(QWidget *parent = nullptr);
    ~Eula();

    bool isEulaRemembered();
    static void showDialog();

private Q_SLOTS:
    void on_cancel_clicked();
    void on_next_clicked();

protected:
    void closeEvent(QCloseEvent *event);
private:
    Ui::Eula *ui;
    bool isRemembered;
};

#endif // BITCOIN_QT_EULA_H
