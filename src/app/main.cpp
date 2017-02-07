#include <QDebug>
#include <QProcess>

#include <DLog>
#include <DApplication>
#include <DWindow>
#include <dutility.h>

#include "bmwindow.h"
#include "bminterface.h"
#include "util/sevenzip.h"
#include "util/utils.h"
#include "util/devicemonitor.h"

DUTIL_USE_NAMESPACE
DWIDGET_USE_NAMESPACE

int main(int argc, char **argv)
{
    DWIDGET_INIT_RESOURCE();

    DApplication app(argc, argv);
    app.setOrganizationName("deepin");
    app.setApplicationName("deepin-boot-maker");
    app.setApplicationDisplayName(DApplication::tr("Deepin Boot Maker"));
    app.setApplicationVersion("1.99.0");
    app.setTheme("light");

//    QCommandLineParser parser;
//    parser.setApplicationDescription("Deepin Boot Maker is a tool to help you make a startup usb disk.");
//    parser.addHelpOption();
//    parser.addVersionOption();

//    QCommandLineOption optImageFile(QStringList() << "f" << "file",
//                                    DApplication::tr("ISO image file"),
//                                    "image-file");
//    QCommandLineOption optKey(QStringList() << "k" << "key",
//                              DApplication::tr("Communication key"),
//                              "key");
//    QCommandLineOption optDaemon(QStringList() << "d" << "daemon",
//                                 DApplication::tr("Run in background"));
//    QCommandLineOption optNoInteractive(QStringList() << "n" << "nointeractive",
//                                        DApplication::tr("Do not run gui"));

//    parser.addOption(optDaemon);
//    parser.addOption(optNoInteractive);
//    parser.addOption(optImageFile);
//    parser.addOption(optKey);
//    parser.addPositionalArgument("device", DApplication::tr("USB Device"));
//    parser.process(app);

    const QString m_format = "%{time}{yyyyMMdd.HH:mm:ss.zzz}[%{type:1}][%{function:-35} %{line:-4} %{threadid} ] %{message}\n";
    DLogManager::setLogFormat(m_format);
    DLogManager::registerConsoleAppender();
    DLogManager::registerFileAppender();

    app.setTheme("light");

    if (!app.setSingleInstance("deepinbootmaker")) {
        qDebug()<< "another deppin music has started";
        exit(0);
    }
#ifdef Q_OS_WIN
    Utils::loadFonts();
#endif

//    if (parser.isSet(optDaemon)) {
//        qDebug() << parser.value(optDaemon)
//                 << parser.value(optNoInteractive)
//                 << parser.value(optImageFile)
//                 << parser.value(optKey)
//                 << parser.positionalArguments();
//        BootMaker bm;
//        qDebug() << "Deepin Boot Maker Backend Started";

//        return app.exec();
//    }

    qDebug() << "Deepin Boot Maker UI started.";

    BMWindow w;
    DUtility::moveToCenter(&w);
    w.show();

//    w.waitAuth();

    auto ret =  app.exec();
    BMInterface::instance()->stop();
    return ret;
}
