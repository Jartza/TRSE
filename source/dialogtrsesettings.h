/*
 * Turbo Rascal Syntax error, “;” expected but “BEGIN” (TRSE, Turbo Rascal SE)
 * 8 bit software development IDE for the Commodore 64
 * Copyright (C) 2018  Nicolaas Ervik Groeneboom (nicolaas.groeneboom@gmail.com)
 *
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program (LICENSE.txt).
 *   If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef DIALOGTRSESETTINGS_H
#define DIALOGTRSESETTINGS_H

#include <QDialog>
#include "source/LeLib/util/cinifile.h"

namespace Ui {
class DialogTRSESettings;
}

class DialogTRSESettings : public QDialog
{
    Q_OBJECT


public:
    explicit DialogTRSESettings(QWidget *parent = 0);

    CIniFile* m_ini;
    void SetInit(CIniFile* ini) {
        m_ini = ini;
        FillFromIni();
    }

    QString fromStringList(QStringList lst) {
        QString whole ="";
        for (QString s: lst) {
            whole+=s;
            if (lst.last()!=s)
                whole=whole+", ";
        }
        return whole;
    }

    QStringList toStringList(QString s) {
        QStringList lst = s.split(",");
        return lst;
    }


    void FillFromIni();
    void FillToIni();

    ~DialogTRSESettings();

private slots:
    void on_pushButton_clicked();

    void on_btnEmulator_clicked();

    void on_btnDasm_clicked();

    void on_btnExomizer_clicked();

    void on_btnEmulatorC128_clicked();

    void on_btnVic20Emulator_clicked();

    void on_btnNesEmulatr_clicked();

    void on_btnC1541Emulator_clicked();

    void on_btnTinyCrunch_clicked();

    void on_btnVasmm_clicked();

    void on_btn68kTargetDir_clicked();

private:
    Ui::DialogTRSESettings *ui;
};

#endif // DIALOGTRSESETTINGS_H
