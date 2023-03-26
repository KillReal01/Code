#include "application.h"
#include "matrix.h"
#include "common.h"

TApplication::TApplication(int argc, char *argv[])
            : QCoreApplication(argc,argv)
{
    TCommParams pars = { QHostAddress("127.0.0.1"), 10000, QHostAddress("127.0.0.1"), 10001};
    comm = new TCommunicator(pars, this);
    connect(comm,SIGNAL(recieved(QByteArray)),this,SLOT(recieve(QByteArray)));
}

void TApplication::recieve(QByteArray msg)
{
    QString answer, s;

    int pos = msg.indexOf(separator.toLatin1());
    int size = msg.left(pos).toInt();
    msg = msg.right(msg.length() - pos - 1);

    TMatrix mtx(size, msg);

    msg = msg.right(6);
    qDebug() << msg.toInt();

    //reduce ;
    pos = msg.indexOf(separator.toLatin1());

    int t = msg.left(pos).toInt();
    switch (t) {
    case DETERMINANT:
        //number ans = mtx.det();
        //s << ans;
        answer << QString().setNum(DETERMINANT);
        answer += s;
        break;
    case RANK:
        //int r = mtx.rank();
        //s << QString::number(r);
        answer << QString().setNum(RANK);
        answer += s;
        break;
    case TRANSPOSE:
        mtx.transpose();
        //int d = mtx.getDim();
//        number **m = mtx.getMtx();
//        for (int i = 0; i < d; i++) {
//            for (int j = 0; j < d; j++) {
//                s << m[i][j];
//            }
//        }

//        for (int i = 0; i < d; i++) {
//            delete[] m[i];
//        }
//        delete[] m;

        break;
    default:
        return;
    }
    //comm->send(QByteArray().append(answer));
    comm->send(answer.toUtf8());
}
