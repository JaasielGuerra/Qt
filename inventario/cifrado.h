#ifndef CIFRADO_H
#define CIFRADO_H
#include <QString>
#include <QCryptographicHash>
#endif // CIFRADO_H

class Cifrado {
    public:
        /*
         * Utiliza el algoritmo Sha2 a 256 bis para cifrar las contrasenias
         * Default
        */
        QString cifrar(QString data) {
            QString Data = data;
            QCryptographicHash* hash;
            QByteArray resultado = hash->hash(Data.toUtf8(), QCryptographicHash::Sha256);

            QString DataHash(resultado.toHex());

            return DataHash;
        }

        /*
         * Utiliza el algoritmo md5 a 128 bis para cifrar la informacion
        */
        QString cifrarMd5(QString data) {
            QString Data = data;
            QCryptographicHash* hash;
            QByteArray resultado = hash->hash(Data.toUtf8(), QCryptographicHash::Md5 );

            QString DataHash(resultado.toHex());

            return DataHash;
        }
};
