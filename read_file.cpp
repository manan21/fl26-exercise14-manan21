// read_file.cpp
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QList>
#include <QString>

#include <cstdlib>

#include "file_header.h"

int main(int argc, char *argv[])
{
  QFile file("temp.dat");
  if (!file.open(QIODevice::ReadOnly)) {
    qCritical() << "Error: unable to open file for reading:" << file.errorString();
    return EXIT_FAILURE;
  }
  QDataStream in(&file);

  // Read and check the header
  quint32 magic;
  in >> magic;
  if (in.status() != QDataStream::Ok) {
    qCritical() << "Error: unable to read file header.";
    return EXIT_FAILURE;
  }
  if (magic != MAGIC){
    qDebug() << "Error: unexpected format.";
    return EXIT_FAILURE;
  }

  // Read the version
  qint32 version;
  in >> version;
  if (in.status() != QDataStream::Ok) {
    qCritical() << "Error: unable to read file version.";
    return EXIT_FAILURE;
  }
  if(version != VERSION){
    qDebug() << "Error: unsupported file version.";
    return EXIT_FAILURE;
  }

  // use the same encoding format
  in.setVersion(QDataStream::Qt_5_0);

  // Read the data
  QList<QString> messages;
  in >> messages;
  if (in.status() != QDataStream::Ok) {
    qCritical() << "Error: unable to read string list.";
    return EXIT_FAILURE;
  }

  qDebug() << "Read data from a file:" << messages;
  
  return EXIT_SUCCESS;
}
