// Copyright 2024 Chun-Yao Hsieh @ Columbia University. All rights reserved.
#include <iostream>
#include "MyApp.h"


MyFileDatabase* MyApp::myFileDatabase = nullptr;
bool MyApp::saveData = false;

void MyApp::run(const std::string& mode) {
    saveData = true;
    if (mode == "setup") {
        setupDatabase();
        std::cout << "System Setup" << std::endl;
        return;
    }
    myFileDatabase = new MyFileDatabase(0, "testfile.bin");
    std::cout << "Start up" << std::endl;
}

void MyApp::onTermination() {
    std::cout << "Termination" << std::endl;
    if (saveData && myFileDatabase) {
        myFileDatabase->saveContentsToFile();
    }
    delete myFileDatabase;
    myFileDatabase = nullptr;
}

void MyApp::overrideDatabase(MyFileDatabase* testData) {
    delete myFileDatabase;
    myFileDatabase = testData;
    saveData = false;
}

MyFileDatabase *MyApp::getDatabase() {
    return myFileDatabase;
}

void MyApp::setupDatabase() {
    myFileDatabase = new MyFileDatabase(1, "testfile.bin");
    resetDataFile();
}

void MyApp::resetDataFile() {
    std::string times[] = {"11:40-12:55", "4:10-5:25", "10:10-11:25", "2:40-3:55"};
    std::string locations[] = {"417 IAB", "309 HAV", "301 URIS"};

    // Data for COMS department
    auto coms1004 = std::make_shared<Course>(400, "Adam Cannon", locations[0], times[0]);
    coms1004->setEnrolledStudentCount(249);
    auto coms3134 = std::make_shared<Course>(250, "Brian Borowski", locations[2], times[1]);
    coms3134->setEnrolledStudentCount(242);
    auto coms3157 = std::make_shared<Course>(400, "Jae Lee", locations[0], times[1]);
    coms3157->setEnrolledStudentCount(311);
    auto coms3203 = std::make_shared<Course>(250, "Ansaf Salleb-Aouissi", locations[2], times[2]);
    coms3203->setEnrolledStudentCount(215);
    auto coms3261 = std::make_shared<Course>(150, "Josh Alman", locations[0], times[3]);
    coms3261->setEnrolledStudentCount(140);
    auto coms3251 = std::make_shared<Course>(125, "Tony Dear", "402 CHANDLER", "1:10-3:40");
    coms3251->setEnrolledStudentCount(99);
    auto coms3827 = std::make_shared<Course>(300, "Daniel Rubenstein", "207 Math", times[2]);
    coms3827->setEnrolledStudentCount(283);
    auto coms4156 = std::make_shared<Course>(120, "Gail Kaiser", "501 NWC", times[2]);
    coms4156->setEnrolledStudentCount(109);

    std::map<std::string, std::shared_ptr<Course>> courses;
    courses["1004"] = coms1004;
    courses["3134"] = coms3134;
    courses["3157"] = coms3157;
    courses["3203"] = coms3203;
    courses["3261"] = coms3261;
    courses["3251"] = coms3251;
    courses["3827"] = coms3827;
    courses["4156"] = coms4156;

    Department coms("COMS", courses, "Luca Carloni", 2700);

    // Data for ECON department
    auto econ1105 = std::make_shared<Course>(210, "Waseem Noor", locations[1], times[3]);
    econ1105->setEnrolledStudentCount(187);
    auto econ2257 = std::make_shared<Course>(125, "Tamrat Gashaw", "428 PUP", times[2]);
    econ2257->setEnrolledStudentCount(63);
    auto econ3211 = std::make_shared<Course>(96, "Murat Yilmaz", "310 FAY", times[1]);
    econ3211->setEnrolledStudentCount(81);
    auto econ3213 = std::make_shared<Course>(86, "Miles Leahey", "702 HAM", times[1]);
    econ3213->setEnrolledStudentCount(77);
    auto econ3412 = std::make_shared<Course>(86, "Thomas Piskula", "702 HAM", times[0]);
    econ3412->setEnrolledStudentCount(81);
    auto econ4415 = std::make_shared<Course>(110, "Evan D Sadler", locations[1], times[2]);
    econ4415->setEnrolledStudentCount(63);
    auto econ4710 = std::make_shared<Course>(86, "Matthieu Gomez", "517 HAM", "8:40-9:55");
    econ4710->setEnrolledStudentCount(37);
    auto econ4840 = std::make_shared<Course>(108, "Mark Dean", "142 URIS", times[3]);
    econ4840->setEnrolledStudentCount(67);

    courses.clear();
    courses["1105"] = econ1105;
    courses["2257"] = econ2257;
    courses["3211"] = econ3211;
    courses["3213"] = econ3213;
    courses["3412"] = econ3412;
    courses["4415"] = econ4415;
    courses["4710"] = econ4710;
    courses["4840"] = econ4840;

    Department econ("ECON", courses, "Michael Woodford", 2345);

    // Data for IEOR department
    auto ieor2500 = std::make_shared<Course>(50, "Uday Menon", "627 MUDD", times[0]);
    ieor2500->setEnrolledStudentCount(52);
    auto ieor3404 = std::make_shared<Course>(73, "Christopher J Dolan", "303 MUDD", times[2]);
    ieor3404->setEnrolledStudentCount(80);
    auto ieor3658 = std::make_shared<Course>(96, "Daniel Lacker", "310 FAY", times[2]);
    ieor3658->setEnrolledStudentCount(87);
    auto ieor4102 = std::make_shared<Course>(110, "Antonius B Dieker", "209 HAM", times[2]);
    ieor4102->setEnrolledStudentCount(92);
    auto ieor4106 = std::make_shared<Course>(150, "Kaizheng Wang", "501 NWC", times[2]);
    ieor4106->setEnrolledStudentCount(161);
    auto ieor4405 = std::make_shared<Course>(80, "Yuri Faenza", "517 HAV", times[0]);
    ieor4405->setEnrolledStudentCount(19);
    auto ieor4511 = std::make_shared<Course>(150, "Michael Robbins", "633 MUDD", "9:00-11:30");
    ieor4511->setEnrolledStudentCount(50);
    auto ieor4540 = std::make_shared<Course>(60, "Krzysztof M Choromanski", "633 MUDD", "7:10-9:40");
    ieor4540->setEnrolledStudentCount(33);

    courses.clear();
    courses["2500"] = ieor2500;
    courses["3404"] = ieor3404;
    courses["3658"] = ieor3658;
    courses["4102"] = ieor4102;
    courses["4106"] = ieor4106;
    courses["4405"] = ieor4405;
    courses["4511"] = ieor4511;
    courses["4540"] = ieor4540;

    Department ieor("IEOR", courses, "Jay Sethuraman", 67);

    // Data for CHEM department
    auto chem1403 = std::make_shared<Course>(120, "Ruben M Savizky", locations[1], "6:10-7:25");
    chem1403->setEnrolledStudentCount(100);
    auto chem1500 = std::make_shared<Course>(46, "Joseph C Ulichny", "302 HAV", "6:10-9:50");
    chem1500->setEnrolledStudentCount(50);
    auto chem2045 = std::make_shared<Course>(50, "Luis M Campos", "209 HAV", "1:10-2:25");
    chem2045->setEnrolledStudentCount(29);
    auto chem2444 = std::make_shared<Course>(150, "Christopher Eckdahl", locations[1], times[0]);
    chem2444->setEnrolledStudentCount(150);
    auto chem2494 = std::make_shared<Course>(24, "Talha Siddiqui", "202 HAV", "1:10-5:00");
    chem2494->setEnrolledStudentCount(18);
    auto chem3080 = std::make_shared<Course>(60, "Milan Delor", "209 HAV", times[2]);
    chem3080->setEnrolledStudentCount(18);
    auto chem4071 = std::make_shared<Course>(42, "Jonathan S Owen", "320 HAV", "8:40-9:55");
    chem4071->setEnrolledStudentCount(29);
    auto chem4102 = std::make_shared<Course>(28, "Dalibor Sames", "320 HAV", times[2]);
    chem4102->setEnrolledStudentCount(27);

    courses.clear();
    courses["1403"] = chem1403;
    courses["1500"] = chem1500;
    courses["2045"] = chem2045;
    courses["2444"] = chem2444;
    courses["2494"] = chem2494;
    courses["3080"] = chem3080;
    courses["4071"] = chem4071;
    courses["4102"] = chem4102;

    Department chem("CHEM", courses, "Laura J. Kaufman", 250);

    // Data for PHYS department
    auto phys1001 = std::make_shared<Course>(150, "Szabolcs Marka", "301 PUP", times[3]);
    phys1001->setEnrolledStudentCount(125);
    auto phys1221 = std::make_shared<Course>(150, "James G. Mccann", "301 PUP", "4:10-5:25");
    phys1221->setEnrolledStudentCount(118);
    auto phys1520 = std::make_shared<Course>(400, "Victor G. Moffat", "630 MUDD", times[1]);
    phys1520->setEnrolledStudentCount(400);
    auto phys2000 = std::make_shared<Course>(100, "Frank E. L. Banta", "402 CHANDLER", "1:10-3:40");
    phys2000->setEnrolledStudentCount(98);
    auto phys3801 = std::make_shared<Course>(150, "Katherine M. McMahon", "603 MUDD", "4:10-5:25");
    phys3801->setEnrolledStudentCount(96);
    auto phys4205 = std::make_shared<Course>(60, "Michael P. Larkin", locations[1], "6:10-9:50");
    phys4205->setEnrolledStudentCount(60);

    courses.clear();
    courses["1001"] = phys1001;
    courses["1221"] = phys1221;
    courses["1520"] = phys1520;
    courses["2000"] = phys2000;
    courses["3801"] = phys3801;
    courses["4205"] = phys4205;

    Department phys("PHYS", courses, "Marcia L. Newson", 200);

    // Setup mapping
    std::map<std::string, Department> mapping;
    mapping["COMS"] = coms;
    mapping["ECON"] = econ;
    mapping["IEOR"] = ieor;
    mapping["CHEM"] = chem;
    mapping["PHYS"] = phys;

    myFileDatabase->setMapping(mapping);
}
