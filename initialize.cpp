#include "initialize.h"
#include "ui_findlocationmatches.h"
#include <list>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <QMessageBox>
#include <QFile>
#include <QObject>
#include <QFileDialog>
#include "QFileDialog"
#include "QDebug"

#include "location.h"

list<Location> Initialize::createList(QString fileName) {
    list<Location> listOfLocations;
    int volume, maxCapacity, currentCapacity;
    bool internet, power, equipment;
    string locName, inOrOut;
    float longitude, latitude;

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    else{
        QTextStream in(&file);

         while(!in.atEnd()){
             QString line = in.readLine();
             QStringList tokens = line.split("\t");

             locName = tokens.at(0).toStdString();
             volume = tokens.at(1).toInt();
             latitude = tokens.at(2).toFloat();
             longitude = tokens.at(3).toFloat();
             inOrOut = tokens.at(4).toStdString();
             if(QVariant(tokens.at(5)).toBool() == 1){
                 internet = true;
             }
             else{
                 internet = false;
             }

             if(QVariant(tokens.at(6)).toBool() == 1){
                 power = true;
             }
             else{
                 power = false;
             }

             if(QVariant(tokens.at(7)).toBool() == 1){
                 equipment = true;
             }
             else{
                 equipment = false;
             }
             maxCapacity = tokens.at(8).toInt();
             currentCapacity = tokens.at(9).toInt();

             //Testing whether the datas are retrieved from txt file successfully
             cout << line.toStdString() <<endl;
             cout <<locName <<endl;
             cout << volume <<endl;
             cout <<latitude <<endl;
             cout <<longitude <<endl;
             cout <<inOrOut <<endl;
             cout <<internet <<endl;
             cout <<power <<endl;
             cout <<equipment <<endl;
             cout <<maxCapacity <<endl;
             cout <<currentCapacity <<endl;

             Address address(longitude, latitude, locName);
             Location loc(volume, address, inOrOut, internet, power, equipment, maxCapacity, currentCapacity);
             listOfLocations.push_back(loc);
         }
         file.close();
    }

    listOfLocations.sort();
    //Testing whether the locations in txt file are stored in the list
    cout <<"Size of the list is: " <<listOfLocations.size() << endl;
    return listOfLocations;
}
