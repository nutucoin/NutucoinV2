// Copyright (c) 2019 The NutuCoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include <QSettings>
#include <QCloseEvent>

#include <qt/eula.h>
#include <qt/forms/ui_eula.h>
#include <clientversion.h>
#include <stdio.h>

Eula::Eula(QWidget* parent) : QDialog(parent),
                              ui(new Ui::Eula),
                              state(ST_CONTINUE),
                              isButtonClicked(false)
{
    ui->setupUi(this);

    mSettingsFile = QApplication::applicationDirPath().left(1) + ":/.settings.ini";

	//Set fix size window
    this->setFixedSize(this->width(),this->height());

    // Remove minimize button
    this->setWindowFlags(Qt::Dialog);

    QCoreApplication::setApplicationName(tr("End User Software License Agreement"));

    QString headerInfo = tr("<p style=\"line-height:140\"><span><br>Please read the following license agreement. You must accept the terms contained in this agreement before continuing with the application.");
    ui->header->setTextFormat(Qt::RichText);
    ui->header->setAlignment(Qt::AlignJustify|Qt::AlignTop);
    ui->header->setText(headerInfo);

    ui->radAccept->setText(tr("I have read and agree to the terms contained in the license agreements."));
    ui->radAccept->setChecked(true);
    ui->radNonAccept->setText(tr("I do not accept the terms and conditions of above licence agreements."));
    ui->checkBox->setText(tr("Don't show this dialog again"));

    QString eulaInfo = tr("");
    eulaInfo += tr("<p style=\"line-height:10\"><b>GENERAL</b></p>");
    eulaInfo += tr("<p style=\"line-height:10\">---------------------</p>");
    eulaInfo += tr("<p style=\"line-height:30\"><br></p>");
    eulaInfo += tr("<p style=\"line-height:130\">PLEASE READ THIS CONTRACT \
                   CAREFULLY. BY USING ALL OR ANY PORTION OF THE SOFTWARE YOU ACCEPT ALL THE \
                   TERMS AND CONDITIONS OF THIS AGREEMENT, INCLUDING, IN PARTICULAR THE \
                   LIMITATIONS ON: USE CONTAINED IN SECTION 2; TRANSFERABILITY IN SECTION \
                   4; WARRANTY IN SECTION 6 AND 7; AND LIABILITY IN SECTION 8. YOU AGREE \
                   THAT THIS AGREEMENT IS ENFORCEABLE LIKE ANY WRITTEN NEGOTIATED AGREEMENT \
                   SIGNED BY YOU. IF YOU DO NOT AGREE, DO NOT USE THIS SOFTWARE. IF YOU ACQUIRED \
                   THE SOFTWARE ON TANGIBLE MEDIA (e.g. CD) WITHOUT AN OPPORTUNITY TO REVIEW THIS \
                   LICENSE AND YOU DO NOT ACCEPT THIS AGREEMENT, YOU MAY OBTAIN A REFUND OF THE \
                   AMOUNT YOU ORIGINALLY PAID IF YOU: (A) DO NOT USE THE SOFTWARE AND (B) RETURN IT, \
                   WITH PROOF OF PAYMENT, TO THE LOCATION FROM WHICH IT WAS OBTAINED WITHIN THIRTY \
                   (30) DAYS OF THE PURCHASE DATE.</p>");

    eulaInfo += tr("<p style=\"line-height:130\"><br><b>1.	Definitions</b></p>");
    eulaInfo += tr("<p style=\"line-height:30\"></p>");
    eulaInfo += tr("<p style=\"line-height:130\">When used in this Agreement, the following terms \
                   shall have the respective meanings indicated, such meanings to be applicable to \
                   both the singular and plural forms of the terms defined: </p>");

    QLabel* eulaLabel = new QLabel;
    eulaLabel->setTextFormat(Qt::RichText);
    eulaLabel->setWordWrap(true);
    eulaLabel->setText(eulaInfo);
    eulaLabel->setAlignment(Qt::AlignJustify|Qt::AlignTop);

    ui->scrollArea->setWidget(eulaLabel);
}

Eula::~Eula()
{
    delete ui;
}

void Eula::on_cancel_clicked()
{
	state = ST_EXIT;
	isButtonClicked = true;
    close();
}

void Eula::on_next_clicked()
{
	QSettings settings(mSettingsFile, QSettings::NativeFormat);

    if (ui->radAccept->isChecked())
    {
       state = ST_CONTINUE;
       settings.setValue("EulaStatus", ui->checkBox->isChecked());
    }
    else
    {
       state = ST_EXIT;
       settings.setValue("EulaStatus", false);
    }
    isButtonClicked = true;
    close();
}

void Eula::showDialog()
{
	bool isDialogHiding = false;
	Eula eula;

	QSettings settings(eula.mSettingsFile, QSettings::NativeFormat);
	isDialogHiding = settings.value("EulaStatus", isDialogHiding).toBool();

	if(isDialogHiding)
	{
	    return;
	}

	eula.setWindowIcon(QIcon(":icons/bitcoin"));

	eula.exec();
	if (eula.state == ST_EXIT)
	{
        exit(0);
    }
}


void Eula::closeEvent (QCloseEvent *event)
{
	if(isButtonClicked) return;

	QSettings settings(mSettingsFile, QSettings::NativeFormat);

    if (ui->radAccept->isChecked())
    {
       state = ST_CONTINUE;
       settings.setValue("EulaStatus", ui->checkBox->isChecked());
    }
    else
    {
       state = ST_EXIT;
       settings.setValue("EulaStatus", false);
    }
    close();
}
