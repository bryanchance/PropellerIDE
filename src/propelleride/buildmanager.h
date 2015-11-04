#pragma once

#include <QObject>
#include <QString>
#include <QLabel>
#include <QComboBox>
#include <QProcess>
#include <QMutex>
#include <QDebug>
#include <QPlainTextEdit>
#include <QDialog>
#include <QHBoxLayout>
#include <QDir>
#include <QMessageBox>
#include <QApplication>
#include <QThread>
#include <QScrollBar>
#include <QFileInfo>
#include <QTimer>

#include "buildstatus.h"
#include "propellerloader.h"

class BuildManager : public QWidget
{
    Q_OBJECT
public:
    explicit BuildManager(QWidget *parent = 0);
    ~BuildManager();
    void show();
    void hide();
    void waitClose();
    void setFont(const QFont & font);

    void setParameters(
            QString comp,
            QString incl,
            QString projFile);

signals:
    void compilerErrorInfo(QString file, int line);
    void terminalReceived(QString text);

public slots:
    virtual void compilerError(QProcess::ProcessError error);
    virtual void compilerFinished(int exitCode, QProcess::ExitStatus status);
    virtual void procReadyRead();
    int runProcess(const QString & programName, const QStringList & programArgs);

public:
    QString compilerStr;
    QString includesStr;
    QString projectFile;
    QString compileResult;

    int loadProgram(PropellerManager * manager,
                    const QString & filename,
                    const QString & port,
                    bool write);

    int runCompiler(QString options = QString());
    void getCompilerOutput();

private:
    QProcess * proc;

    QMutex      procMutex;
    bool        procDone;

    BuildStatus * console;
    QPlainTextEdit * consoleEdit;

    QTimer timer;
};
