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

#ifndef FORMRASEDITOR_H
#define FORMRASEDITOR_H

#include <QWidget>
#include "trsedocument.h"
#include "source/PmmEdit/highlighter.h"
#include "source/PmmEdit/codeeditor.h"
#include "source/messages.h"
#include "source/Compiler/lexer.h"
#include "source/Compiler/parser.h"
#include "source/Compiler/compiler.h"
#include <QElapsedTimer>
#include "source/dialoghelp.h"
#include "source/dialogmemoryanalyze.h"
#include "source/Compiler/misc/machinecodeanalyzer.h"
#include "source/OrgAsm/orgasm.h"
#include "source/OrgAsm/orgasmlexer.h"

#include "source/Compiler/systems/abstractsystem.h"
#include "source/Compiler/systems/factorysystem.h"

#include "source/Compiler/sourcebuilder.h"

#include <QThread>
#include <QElapsedTimer>

namespace Ui {
    class FormRasEditor;
}


/*class Builder : public QThread  {
public:




};
*/

class BuilderThread : public QThread {
    Q_OBJECT
public:
    SourceBuilder* m_builder = nullptr;
    QString m_source, m_filename;
    bool m_isRunning = false;
    void run() override;

signals:
    void emitText();
    void emitSuccess();
    void emitError();

};


class FormRasEditor : public TRSEDocument
{
    Q_OBJECT

public:
    explicit FormRasEditor(QWidget *parent = 0);
    ~FormRasEditor();
    Highlighter* highlighter = nullptr;
    QFont m_font;
    bool m_run = false;
    QVector<int> m_blockEndSymbols;

    BuilderThread m_builderThread;
    QElapsedTimer m_timer;
    int m_lastBuild= 0;

    MachineCodeAnalyzer m_mca;
    QString filename;
    bool isInitialized=false;
    int m_searchFromPos = 0;
    int m_currentFromPos = 0;

    void LoadRasFile(QString fileName);
    void ExecutePrg(QString fileName,  QString system);
    void InitDocument(WorkerThread *t, CIniFile *ini, CIniFile* iniProject) override;
    void setupEditor();
    void Compress();
    void Build() override;
    bool BuildDiskFiles(QStringList& d64Params, QString data);
    void Setup();



    void Run() override;
    void SetLights();
    void SetText(QString s);
    void SetupHighlighter();
    void SearchInSource();
    void UpdateColors() override;
    void UpdateFromIni() override;
    void AutoFormat() override;
  //  bool BuildStep();
    void Assemble6502(QString& text);
    void FillFromIni();
    void FillToIni();

    void MemoryAnalyze() override;


    void Reload() override;

    void Save(QString filename) override;
    void Load(QString filename) override;
    void wheelEvent(QWheelEvent *event) override;
    void keyPressEvent(QKeyEvent* e) override;

    void Destroy() override {}
    void TestForCodeOverwrite(int codeEnd, QString& output);
    void GotoLine(int ln) override;

    Ui::FormRasEditor* UI(){return ui;}

    void SetOutputText(QString txt);

    int FindEndSymbol(Orgasm& orgAsm);
    void FindBlockEndSymbols(Orgasm& orgAsm);
    void ConnectBlockSymbols();
    void BuildNes(QString prg);

private:

//    bool VerifyMachineCodeZP(QString fname);

    static QString path;
    Ui::FormRasEditor *ui;

signals:
    void OpenOtherFile(QString filename, int ln);

private slots:
    void on_leSearch_textChanged();

    void on_leSearch_returnPressed();

    void on_leSearch_textChanged(const QString &arg1);

    void on_btnReplace_clicked();
    void on_chkExomize_stateChanged(int arg1);
    void on_chkPostOpt_stateChanged(int arg1);


    void HandleUpdateBuildText();
    void HandleBuildComplete();
    void HandleBuildError();
    void HandleErrorDialogs(QString& output);
//    void HandleRun();
};

#endif // FORMRASEDITOR_H
