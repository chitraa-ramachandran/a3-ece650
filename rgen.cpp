#include<iostream>
#include<sstream>
#include<vector>
#include<fstream>
#include<unistd.h>
#include<cmath>
#include<cstring>

using namespace std;

class Point
{
private:
    int xCord;
    int yCord;

public:
    Point(int x, int y)
    {
        xCord = x;
        yCord = y;
    }

    void setXCord(int x)
    {
        xCord = x;
    }

    int getXCord()
    {
        return xCord;
    }

    void setYCord(int y)
    {
        yCord = y;
    }

    int getYCord()
    {
        return yCord;
    }
};

class Street
{
private:
    string streetName;
    vector<Point> coOrdinates;

public:
    Street()
    {
        //doNothing
    }

    void setStreetName(string sName)
    {
        streetName = sName;
    }

    string getStreetName()
    {
        return streetName;
    }

    void addCoOrdinates(Point p1)
    {
        coOrdinates.push_back(p1);
    }

    vector<Point> getCoOrdinates()
    {
        return coOrdinates;
    }
};

class GroupOfStreet
{
private:
    vector<Street> streetList;
public:
    void addStreet(Street s1)
    {
        streetList.push_back(s1);
    }
    vector<Street> getStreetList()
    {
        return streetList;
    }
    void removeAllStreets()
    {
        streetList.clear();
    }

};



class RandomGeneratorParameters
{
private:
    int sUpper;
    int sLower;
    int nUpper;
    int nLower;
    int lUpper;
    int lLower;
    int cUpper;
    int cLower;
public:
    RandomGeneratorParameters()
    {
        sLower = 2;
        sUpper = 10;
        nLower = 1;
        nUpper = 5;
        lLower = 5;
        lUpper = 5;
        cUpper = 20;
        cLower = -20;
    }
    void setSUpper(int sUp)
    {
        sUpper = sUp;
    }

    int getSUpper()
    {
        return sUpper;
    }

    void setSLower(int sLow)
    {
        sLower = sLow;
    }

    int getSLower()
    {
        return sLower;
    }

    void setNUpper(int nUp)
    {
        nUpper = nUp;
    }

    int getNUpper()
    {
        return nUpper;
    }

    void setNLower(int nLow)
    {
        nLower = nLow;
    }

    int getNLower()
    {
        return nLower;
    }
    void setLUpper(int lUp)
    {
        lUpper = lUp;
    }

    int getLUpper()
    {
        return lUpper;
    }

    void setLLower(int lLow)
    {
        lLower = lLow;
    }

    int getLLower()
    {
        return lLower;
    }

    void setCUpper(int cUp)
    {
        cUpper = cUp;
    }

    int getCUpper()
    {
        return cUpper;
    }

    void setCLower(int cLow)
    {
        cLower = cLow;
    }

    int getCLower()
    {
        return cLower;
    }
};

int convertStringtoInt(char *str)
{
    int val;
    stringstream ss(str);
    ss>>val;
    return val;
}

void setArguments(int argc, char** argv, RandomGeneratorParameters *rgp)
{
    for (int i = 0; i < argc; ++i)
        if (strcmp(argv[i],"-s") == 0)
        {
            rgp->setSUpper(convertStringtoInt(argv[i+1]));
        }

        else if(strcmp(argv[i],"-n") == 0)
        {
            rgp->setNUpper(convertStringtoInt(argv[i+1]));
        }

        else if(strcmp(argv[i],"-l") == 0)
        {
            rgp->setLUpper(convertStringtoInt(argv[i+1]));
        }
        else if(strcmp(argv[i],"-c") == 0)
        {
            rgp->setCLower(convertStringtoInt(argv[i+1])*-1);
            rgp->setCUpper(convertStringtoInt(argv[i+1]));
        }
        else
        {
            //do Nothing
        }

    //cout << argv[i] << "\n";
}

void generateInputForPython(GroupOfStreet gos)
{
    vector<Street> streetList = gos.getStreetList();

    for(int i = 0; i < streetList.size(); i++)
    {
        string finalStr = "a ";
        string streetName = streetList[i].getStreetName();
        finalStr += streetName+" ";
        vector<Point> coOrdinates = streetList[i].getCoOrdinates();
        for(int j = 0; j < coOrdinates.size(); j++)
        {
            if(j == coOrdinates.size()-1)
            {
                finalStr+= "("+to_string(coOrdinates[j].getXCord())+","+to_string(coOrdinates[j].getYCord())+")";
            }
            else
            {
                finalStr+= "("+to_string(coOrdinates[j].getXCord())+","+to_string(coOrdinates[j].getYCord())+") ";
            }

        }
        cout<<finalStr<<endl;
    }
    cout<<"g"<<endl;
}

int generateRandomNumber(int lowerLimit, int upperLimit)
{
    if(lowerLimit == upperLimit)
    {
        return upperLimit;
    }
    else
    {
        std::ifstream urandom("/dev/urandom");
        if (urandom.fail()) {
            std::cerr << "Error: cannot open /dev/urandom\n";
            return 1;
        }
        int num = 0;
        urandom.read((char*)&num, 1);
        int randNumber = (int) num;
        randNumber = (randNumber % (upperLimit - lowerLimit))  + lowerLimit;
        urandom.close();
        return randNumber;
    }
}

bool checkForDuplicate(vector<Point> coOrdinates, Point p1)
{
    for(int i = 0; i < coOrdinates.size(); i++)
    {
        if(coOrdinates[i].getXCord() == p1.getXCord() && coOrdinates[i].getYCord() == p1.getYCord())
        {
            return true;
        }
    }
    return false;
}


float distance(Point p1, Point p2)
{
    return  sqrt(pow(p1.getXCord()-p2.getXCord(), 2) + pow(p1.getYCord() - p2.getYCord(), 2));
}

bool isBetween(Point p1, Point p2, Point generatedPoint)
{
    float d1 = distance(p1,generatedPoint);
    float d2 = distance(generatedPoint, p2);
    float d3 = distance(p1,p2);
    if(d1+d2 == d3)
    {
        return true;
    }
    return false;
}

bool checkOnLineSegment(vector<Point> coOrdinates, Point  p1)
{
    if(coOrdinates.size() <= 1)
    {
        return true;
    }
    else
    {
        for(int i = 0; i < coOrdinates.size()-1; i++)
        {
            if(isBetween(coOrdinates[i], coOrdinates[i+1], p1) == true)
            {
                return false;
            }
        }
        return true;
    }


}

int checkOrientation(Point p1, Point p2, Point p3)
{
    int val = (p2.getYCord() - p1.getYCord()) * (p3.getXCord() - p2.getXCord()) - (p2.getXCord() - p1.getXCord()) * (p3.getYCord() - p2.getYCord());

    if(val == 0)
    {
        return 0;
    }
    if(val > 0)
        return 1;
    else
        return 2;

}

bool onSegment(Point p1,Point p2, Point p3)
{
    if(p2.getXCord() <= max(p1.getXCord(), p3.getXCord()) && p2.getXCord() >= min(p1.getXCord(), p3.getXCord()) && p2.getYCord() <= max(p1.getYCord(), p3.getYCord()) && p2.getYCord() >= min(p1.getYCord(), p3.getYCord()))
        return true;
    return false;

}

bool findFinal(Point p1, Point p2, Point q1, Point q2,  int o1, int o2, int o3, int o4)
{
    if(o1 != o2 && o3 != o4)
    {
        return true;
    }
    if(o1 == 0 && onSegment(p1,p2,q1))
    {
        return true;
    }
    if(o2 == 0 && onSegment(p1,q2,q1))
    {
        return true;
    }
    if(o3 == 0 && onSegment(p2,p1,q2))
    {
        return true;
    }
    if(o4 == 0 && onSegment(p2,q1,q2))
    {
        return true;
    }
    return false;
}

bool checkForIntersection(Point p1, Point q1, Point p2, Point q2)
{
    int o1 = checkOrientation(p1,q1,p2);
    int o2 = checkOrientation(p1,q1,q2);
    int o3 = checkOrientation(p2,q2,p1);
    int o4 = checkOrientation(p2,q2,q1);

    bool check = findFinal(p1,q1,p2,q2,o1,o2,o3,o4);
    if(check == false)
    {
        return false;
    }
    return true;
}

bool checkSelfIntersection(vector<Point> coOrdinates, Point p1)
{
    if(coOrdinates.size() <= 3)
    {
        return false;
    }
    else
    {
        for(int i = 0; i < coOrdinates.size()-2; i++)
        {
            if(checkForIntersection(coOrdinates[i], coOrdinates[i+1], coOrdinates[coOrdinates.size()-1], p1) == true)
            {
                return true;
            }
        }
        return false;
    }

}

bool checkForPartialOverlap(GroupOfStreet gos, Street s1, Point p1) {
    vector<Point> coOrdinatesOfLastStreet = s1.getCoOrdinates();
    if (coOrdinatesOfLastStreet.size() == 0) {
        return false;
    }
    vector<Street> allStreets = gos.getStreetList();
    if (allStreets.size() <= 1) {
        return false;
    } else {
        for (int i = 0; i < allStreets.size(); i++) {
            vector<Point> stPoints = allStreets[i].getCoOrdinates();
            for (int j = 0; j < stPoints.size() - 1; j++) {
                if (distance(stPoints[j], coOrdinatesOfLastStreet[coOrdinatesOfLastStreet.size() - 1]) +
                    distance(coOrdinatesOfLastStreet[coOrdinatesOfLastStreet.size() - 1], stPoints[j + 1]) ==
                    distance(stPoints[j], stPoints[j + 1])) {
                    if (distance(coOrdinatesOfLastStreet[coOrdinatesOfLastStreet.size() - 1], stPoints[j + 1]) +
                        distance(stPoints[j + 1], p1) ==
                        distance(coOrdinatesOfLastStreet[coOrdinatesOfLastStreet.size() - 1], p1)) {
                        return true;
                    }
                }

                if (distance(stPoints[j], coOrdinatesOfLastStreet[coOrdinatesOfLastStreet.size() - 1]) +
                    distance(stPoints[j], p1) ==
                    distance(p1, coOrdinatesOfLastStreet[coOrdinatesOfLastStreet.size() - 1])) {
                    if (distance(coOrdinatesOfLastStreet[coOrdinatesOfLastStreet.size() - 1], stPoints[j]) +
                        distance(coOrdinatesOfLastStreet[coOrdinatesOfLastStreet.size() - 1], stPoints[j + 1]) ==
                        distance(stPoints[j], stPoints[j + 1])) {
                        return true;
                    }
                }
            }
            return false;

        }
    }

}

int main(int argc, char** argv) {
    RandomGeneratorParameters rgp;
    setArguments(argc, argv, &rgp);

    GroupOfStreet gos;
    while (true) {
        vector<Street> temp = gos.getStreetList();
        for (int i = 0; i < temp.size(); i++) {
            cout<<"r \""<<temp[i].getStreetName()<<"\" ";;
            cout << endl;
        }
        gos.removeAllStreets();
        int noOfStreets = generateRandomNumber(rgp.getSLower(), rgp.getSUpper());
        bool flagForSpecs = true;
        for (int i = 1; i <= noOfStreets; i++) {
            Street s1;
            s1.setStreetName("Street" + to_string(i));

            int noOfLineSegments = generateRandomNumber(rgp.getNLower(), rgp.getNUpper());
            for (int j = 0; j < noOfLineSegments + 1; j++) {
                int noOfTries = 0;

                while (true) {
                    int xCord = generateRandomNumber(rgp.getCLower(), rgp.getCUpper());
                    int yCord = generateRandomNumber(rgp.getCLower(), rgp.getCUpper());
                    Point p1(xCord, yCord);
                    if (checkForDuplicate(s1.getCoOrdinates(), p1) == false) {
                        if (checkOnLineSegment(s1.getCoOrdinates(), p1) == true) {
                            if (checkSelfIntersection(s1.getCoOrdinates(), p1) == false) {
                                if (checkForPartialOverlap(gos, s1, p1) == false) {
                                    s1.addCoOrdinates(p1);
                                    flagForSpecs = true;
                                    break;
                                }
                            }
                        }
                        noOfTries++;
                        if (noOfTries == 25) {
                            cout << "Error: Failed to generate specification" << endl;
                            break;
                        }
                    }
                }

                if (flagForSpecs == false) {
                    break;
                }
            }
            if (flagForSpecs == false) {
                break;
            }
            gos.addStreet(s1);
        }
        if(flagForSpecs == true)
        {
            generateInputForPython(gos);
        }
        else
        {
            gos.removeAllStreets();
        }
        if (rgp.getLLower() == rgp.getLUpper()) {
            sleep(rgp.getLUpper());
        } else {
            int sleepTime = generateRandomNumber(rgp.getLLower(), rgp.getLUpper());
            sleep(sleepTime);
        }

    }
    return 0;
}

