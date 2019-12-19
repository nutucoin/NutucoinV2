// Copyright (c) 2019 The NutuCoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef NUTU_QT_EULA_H
#define NUTU_QT_EULA_H

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

    static void showDialog();

    enum Status {
        ST_CONTINUE,
        ST_EXIT
    };


private Q_SLOTS:
    void on_cancel_clicked();
    void on_next_clicked();

private:
    Ui::Eula *ui;
    int state;
    void closeEvent(QCloseEvent *event);
    bool isButtonClicked;
    QString mSettingsFile;

};

#endif // NUTU_QT_EULA_H
