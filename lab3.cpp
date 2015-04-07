/**  
*  @file    lab3.cpp  
*  @author  Georgina Hutchins (hutcgb12)
*  @date    02/06/2014  
*  @version 1.0  
*
*  @brief CSC 112, Lab 3, DJIA Index Program 
*
*  @section DESCRIPTION
*
*  This program calculates the daily returns for a given DJIA file 
*  entered by the user. The program reads the DJIA price information
*  in the file and displays the average daily return for the seasons
*  and the single day that had the largest daily return increase.
*
*  @bug No known bugs
*
*/



#include <iostream>
#include <fstream>
using namespace std;



void inputFileName(string& fileName);


double dailyReturn(double price, double oldPrice);


void recordHighestDailyReturn(double dr, int day, int month, int year, double& highDR, int& highDay, int& highMonth, int& highYear);


void recordSeasonDailyReturn(double dr, int month, double& fallSum, int& fallCount, double& winterSum, int& winterCount, double& springSum, int& springCount, double& summerSum, int& summerCount);


void outputResults(double highDR, int highDay, int highMonth, int highYear, double fallSum, int fallCount, double winterSum, int winterCount, double springSum, int springCount, double summerSum, int summerCount, string fileName);



int main()
{
	int year = 0;		///< Year value from each line of the file
	int month = 0;		///< Month value from each line of the file
	int day = 0;		///< Day value from each line of the file
	int highYear = 0;	///< Year with the largest return increase
	int highMonth = 0;	///< Month with the largest return increase
	int highDay = 0;	///< Day with the largest return increase
	double price = 0;	///< Current price for each day from the file
	double oldPrice;	///< Previous day's price from the file
	double dr = 0;		///< Daily return for a given day
	double highDR = 0;	///< Largest daily return value
	double fallSum = 0;	///< Sum of the daily returns for the fall
	int fallCount = 0;	///< Number of daily prices for the fall
	double winterSum = 0;	///< Sum of the daily returns for the winter
	int winterCount = 0;	///< Number of daily prices for the winter
	double springSum = 0;	///< Sum of the daily returns for the spring
	int springCount = 0;	///< Number of daily prices for the spring
	double summerSum = 0;	///< Sum of the daily returns for the summer
	int summerCount = 0;	///< Number of daily prices for the summer
	string fileName;	///< Variable that stores the DJIA filename 


	inputFileName(fileName);
	fstream dataFile(fileName.c_str(), ios :: in);
	dataFile >> year >> month >> day >> oldPrice;

	while (dataFile >> year >> month >> day >> price)
	{
		dr = dailyReturn(price, oldPrice);
		oldPrice = price;	
	
		recordHighestDailyReturn(dr, day, month, year, highDR, highDay, highMonth, highYear);
		recordSeasonDailyReturn(dr, month, fallSum, fallCount, winterSum, winterCount, springSum, 
		   springCount, summerSum, summerCount);
	}

	dataFile.close();

	outputResults(highDR, highDay, highMonth, highYear, fallSum, fallCount, winterSum, winterCount, 
	   springSum, springCount, summerSum, summerCount, fileName);

	return 0;
}



/**
*  @brief inputFileName is a function that prompts the user and reads
*  in the name of the file
* 
*  @param fileName is the name of the file from user input
*
*  @return void
*/
void inputFileName(string& fileName)
{
	cout << "Enter the DJIA file name -> ";
	cin >> fileName;
}



/**
*  @brief dailyReturn is a function that returns the daily return
*  given current and previous prices
*
*  @param price is the current day's price
*  @param oldPrice is the previous day's price
*
*  @return the daily return value, which is the change in the
*  current price as a percentage of the previous day's closing price
*/
double dailyReturn(double price, double oldPrice)
{
	return (((price / oldPrice) - 1 ));
}



/**
*  @brief recordHighestDailyReturn is a function that will record the
*  highest daily return observed so far in the file
*
*  @param dr is the current daily return
*  @param day is the current day
*  @param month is the current month
*  @param year is the current year
*  @param highDR is the highest daily return thus far
*  @param highDay is the day of the highest DR thus far
*  @param highMonth is the month of the highest DR thus far
*  @param highYear is the year of the highest DR thus far
*
*  @return void
*/
void recordHighestDailyReturn(double dr, int day, int month, int year, double& highDR, int& highDay, int& highMonth, int& highYear)
{
	if (dr > highDR)
	{
		highDR = dr;
		highDay = day;
		highMonth = month;
		highYear = year;
	}
}



/** 
*  @brief recordSeasonDailyReturn is a function that given a date
*  and daily return will update the appropriate seasonal daily return
*
*  @param dr is the current daily return
*  @param month is the current month; control statements separated
*  by season
*  @param fallSum is the sum of the daily returns in the fall
*  @param fallCount is the number of daily prices for fall
*  @param winterSum is the sum of the daily returns in the winter
*  @param winterCount is the number of daily prices for winter
*  @param springSum is the sum of the daily returns in the spring
*  @param springCount is the number of daily prices for spring
*  @param summerSum is the sum of the daily returns in the summer
*  @param summerCount is the number of daily prices for summer
*  
*  @return void
*/
void recordSeasonDailyReturn(double dr, int month, double& fallSum, int& fallCount, double& winterSum, int& winterCount, double& springSum, int& springCount, double& summerSum, int& summerCount)
{
	if (month == 9 || month == 10 || month == 11)
	{
		fallSum += dr;
		fallCount ++;
	}

	if (month == 12 || month == 1 || month == 2)
	{
		winterSum += dr;
		winterCount ++;
	}

	if (month == 3 || month == 4 || month == 5)
	{
		springSum += dr;
		springCount ++;
	}

	if (month == 6 || month == 7 || month == 8)
	{
		summerSum += dr;
		summerCount ++;
	}
}



/**
*  @brief outputResults is a function that displays the seasonal and
*  highest daily returns for the file
*
*  @param highDR is the higest daily return from the file
*  @param highDay is the day of the highest daily return
*  @param highMonth is the month of the highest daily return
*  @param highYear is the year of the highest daily return
*  @param fallSum is the sum of daily returns in the fall
*  @param fallCount is the number of daily prices for fall
*  @param winterSum is the sum of daily returns in the winter
*  @param winterCount is the number of daily prices for winter
*  @param springSum is the sum of daily returns in the spring
*  @param springCount is the number of daily prices for spring
*  @param summerSum is the sum of daily returns in the summer
*  @param summerCount is the number of daily prices for summer
*  @param fileName is the name of the file from user input
*
*  @return void
*/
void outputResults(double highDR, int highDay, int highMonth, int highYear, double fallSum, int fallCount, double winterSum, int winterCount, double springSum, int springCount, double summerSum, int summerCount, string fileName)
{
	double percentHighDR;		///< Percent value of highDR
	double fall;			///< Fall average daily return 
	double winter;			///< Winter average daily return 
	double spring;			///< Spring average daily return
	double summer;			///< Summer average daily return

	fall = ((double) ((fallSum / fallCount) * 100));
	winter = ((double) ((winterSum / winterCount) * 100));
	spring = ((double) ((springSum / springCount) * 100));
	summer = ((double) ((summerSum / summerCount) * 100));
	
	percentHighDR = (highDR * 100);

	cout << "Daily returns for the file:  " << fileName << '\n';
	cout << "Summer:  " << summer << "%, " << "Fall:  " << fall << "%, " << "Winter:  " << winter
	   << "%, " << "Spring:  " << spring << '%' << '\n';
	cout << "Highest daily return:  " << percentHighDR << "%, " << "on " << highMonth << '/' 
	   << highDay << '/' << highYear << '\n';

}











