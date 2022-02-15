#include <QtCore/QCoreApplication>
#include <QTextStream>
#include <Qmap>
#include <QFile>
#include <QRegularExpression>
#include <QStringList>
#include <QCryptographicHash>
#include <QCommandLineParser>
#include <QCommandLineOption>

void fFind(const QString &arg1, const QString &arg2)
{
    QTextStream output(stdout);
    int counter = 0;
    QString find_word = arg1;

    QFile file(arg2);
    if (!file.open(QIODevice::ReadOnly))
        qDebug() << "Error read file";
    
    QString read_file = file.readAll();
    file.close();

    QRegularExpression splitter("[<?!> (.,)]");
    QStringList list = read_file.split(splitter);
    QStringList::iterator qlistiterator;
    for (qlistiterator = list.begin(); qlistiterator != list.end(); ++qlistiterator)
        if (*qlistiterator == arg1)
            ++counter;
    output << "Search word " <<
       "*" << arg1 << "*"
           << " occurs " << counter << " times";
}

void fHash(const QString &arg1, const QString &arg2)
{
    QTextStream output(stdout);
    QString str_hash;
    QFile file(arg2);
    if (!file.open(QIODevice::ReadOnly))
        qDebug() << "Error read file";
        
    if (arg1 == "md4")
    {
        QCryptographicHash hash (QCryptographicHash::Md4);
        QByteArray array = file.readAll();
        file.close();
        hash.addData(array);
        str_hash = hash.result().toHex().data();
        output << str_hash;
    }

    else if (arg1 == "md5")
    {
        QCryptographicHash hash (QCryptographicHash::Md5);
        QByteArray array = file.readAll();
        file.close();
        hash.addData(array);
        str_hash = hash.result().toHex().data();
        output << str_hash;
    }

    else if (arg1 == "sha256")
    {
        QCryptographicHash hash (QCryptographicHash::Sha256);
        QByteArray array = file.readAll();
        file.close();
        hash.addData(array);
        str_hash = hash.result().toHex().data();
        output << str_hash;
    }

    else 
    {
        output << "Invalid second argument";
    }
}

int main(int argc, char *argv[])

{
    QTextStream output(stdout);
    QCoreApplication app(argc, argv);
    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();
    QCoreApplication::setApplicationVersion("1.5");
    QCoreApplication::setApplicationName("Prog");

    QCommandLineOption searchWordOption(QStringList() << "w" << "word", QCoreApplication::translate("main", "Enter search word"), QCoreApplication::translate("main", "word"));
    parser.addOption(searchWordOption);

    QCommandLineOption enterPathOption(QStringList() << "p" << "path", QCoreApplication::translate("main", "Enter path to file"), QCoreApplication::translate("main", "path"));
    parser.addOption(enterPathOption);

    QCommandLineOption typeHashOption(QStringList() << "a" << "hash", QCoreApplication::translate("main", "Enter type hash"), QCoreApplication::translate("main", "hash"));
    parser.addOption(typeHashOption);

    parser.process(app);

    //qDebug() << parser.value(searchWordOption) << parser.value(enterPathOption);
    
    bool isFind = parser.isSet(searchWordOption);
    bool isHash = parser.isSet(typeHashOption);

    if (isFind)
    {
        fFind(parser.value(searchWordOption), parser.value(enterPathOption));
    }

    else if (isHash)
    {
        fHash(parser.value(typeHashOption), parser.value(enterPathOption));
    }
       
    return 0;
    
}
