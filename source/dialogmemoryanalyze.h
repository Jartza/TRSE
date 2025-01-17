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

#ifndef DIALOGMEMORYANALYZE_H
#define DIALOGMEMORYANALYZE_H

#include <QDialog>
#include "source/Compiler/assembler/assembler.h"
#include <QMap>
#include <QImage>
#include <QPainter>
#include <QPixmap>


namespace Ui {
class DialogMemoryAnalyze;
}

class DialogMemoryAnalyze : public QDialog
{
    Q_OBJECT

    int m_fontSize;
    QVector<MemoryBlock*> m_blocks;
    CIniFile* m_iniFile = nullptr;
public:
    explicit DialogMemoryAnalyze(CIniFile* ini, QWidget *parent = 0);
    void Initialize(QVector<MemoryBlock*>& blocks, int fontSize);
    QMap<QString, QColor> m_colors;
    void InitColors();
    void resizeEvent(QResizeEvent *) override;
    void VerifyZPMusic(QVector<MemoryBlock*> &blocks);
    ~DialogMemoryAnalyze();

private slots:
    void on_btnClose_clicked();

private:
    Ui::DialogMemoryAnalyze *ui;
};

#endif // DIALOGMEMORYANALYZE_H
