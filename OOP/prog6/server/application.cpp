#include "application.h"
#include "common.h"
#include "square_matrix.h"
#include "complex.h"
#include "rational.h"

TApplication::TApplication(int argc, char *argv[])
            : QCoreApplication(argc,argv)
{
    TCommParams pars = { QHostAddress("127.0.0.1"), 10000, QHostAddress("127.0.0.1"), 10001};
    comm = new TCommunicator(pars, this);

    connect(comm, SIGNAL(recieved(QByteArray)), this, SLOT(recieve(QByteArray)));
}

void TApplication::recieve(QByteArray msg)
{
    QString answer, s;

    //извлекаем режим работы

    int pos = msg.indexOf(separator.toLatin1());
    int mode = msg.left(pos).toInt();
    msg = msg.right(msg.length() - pos - 1);

    //извлекаем размер матрицы
    pos = msg.indexOf(separator.toLatin1());
    int size = msg.left(pos).toInt();
    msg = msg.right(msg.length() - pos - 1);

    //извлекаем матрицу
    switch (mode) {
    case REAL_MODE: {
        TSquareMatrix<double> mtx(size, msg);
        pos = msg.indexOf(separator.toLatin1());
        int operation = msg.left(pos).toInt();

        switch (operation) {
        case DETERMINANT:
        {
            double ans;
            ans = mtx.det();
            s << QString::number(ans);
            answer << QString().setNum(DETERMINANT);
            answer += s;
            break;
        }
        case RANK:
        {
            int r = mtx.rank();
            s << QString::number(r);
            answer << QString().setNum(RANK);
            answer += s;
            break;
        }
        case TRANSPOSE:
        {
            mtx.transpose();
            s << mtx;
            answer << QString().setNum(TRANSPOSE);
            answer += s;
            break;
        }
        default:
            return;
        }
        break;
    }
    case COMPLEX_MODE: {
        TSquareMatrix<TComplex> mtx(size, msg);
        pos = msg.indexOf(separator.toLatin1());
        int operation = msg.left(pos).toInt();

        switch (operation) {
        case DETERMINANT:
        {
            TComplex ans;
            ans = mtx.det();
            s << ans;
            answer << QString().setNum(DETERMINANT);
            answer += s;
            break;
        }
        case RANK:
        {
            int r = mtx.rank();
            s << QString::number(r);
            answer << QString().setNum(RANK);
            answer += s;
            break;
        }
        case TRANSPOSE:
        {
            mtx.transpose();
            s << mtx;
            answer << QString().setNum(TRANSPOSE);
            answer += s;
            break;
        }
        default:
            return;
        }
        break;
    }
    case RATIONAL_MODE: {
        TSquareMatrix<TRational> mtx(size, msg);
        pos = msg.indexOf(separator.toLatin1());
        int operation = msg.left(pos).toInt();

        switch (operation) {
        case DETERMINANT:
        {
            TRational ans;
            ans = mtx.det();
            s << ans;
            answer << QString().setNum(DETERMINANT);
            answer += s;
            break;
        }
        case RANK:
        {
            int r = mtx.rank();
            s << QString::number(r);
            answer << QString().setNum(RANK);
            answer += s;
            break;
        }
        case TRANSPOSE:
        {
            mtx.transpose();
            s << mtx;
            answer << QString().setNum(TRANSPOSE);
            answer += s;
            break;
        }
        default:
            return;
        }
        break;
    }
    }

    //comm->send(QByteArray().append(answer));
    comm->send(answer.toUtf8());
}
