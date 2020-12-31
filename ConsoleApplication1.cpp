// Class       : 18540
// program     : Babbage's Cabbage's, Part 4.
// Autor       : Mohammad Ayub Hanif Saleh.
// Date        : Fall 2020
// Description : This is a program that can compute an employee's weekly
//               gross pay, taxes, and net pay, by using info which were
//              provied by the file to the program such as employee's first and
//               last names, number of hours worked and hourly rate of pay.

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>

#define NUM_EMPLOYEES 14     // Number of employees you want to process.
#define GROSS_PERCENT 0.3     // Constant which is for 30% of gross pay.
#define OVERTIME 40          // Beyond this certain time the overtime kicks in.

void input(std::istream &stream, std::string& full_name, double& hours,
    double& hourly_rate, double& deduction);
void input_full_name(std::istream& stream, std::string &full_name);
std::string join_names(std::string first_name, std::string last_name);
void processing(double& gross_pay, double hours, double hourly_rate,
    double& taxes, double& net_pay, double& regular_hours,
    double& overtime_hours, double deduction);
void hours_spliter(double hours, double& regular_hours,
    double& overtime_hours);
double full_gross_pay(double hours, double hourly_rate, double regular_hours,
    double overtime_hours);
double full_taxes(double gross_pay);
double full_net_pay(double gross_pay, double taxes, double deduction);
void calculation(double gross_pays[], int data, double& total_gross_amount,
    double& average_gross_amount, double& minimum_gross_amount,
    double& maximum_gross_amount, std::string full_names[]);
double total_gross_pay(double gross_pays[], int times);
double average_gross_pay(double gross_pay[], int times);
double minimum_gross_pay(double gross_pays[], int times);
double maximum_gross_pay(double gross_pays[], int times);
void descending_order(std::string full_name[], double gross_pays[], int times);
void show_header(std::ostream& stream);
void summary_header(std::ostream& stream);
void output(std::ostream& stream, std::string full_name, double hours,
    double hourly_rate, double gross_pay, double taxes, double net_pay,
    double regular_hours, double overtime_hours, double deduction);
void summary_output(std::ostream& stream, double total_gross_amount,
    double average_gross_amount, double minimum_gross_amount,
    double maximum_gross_amount, int sum, std::string full_names[],
    double gross_pays[]);

int main()
{
    std::string full_name;
    double hours, hourly_rate, gross_pay, taxes, net_pay, regular_hours,
        overtime_hours, deduction, total_gross_amount, average_gross_amount,
        minimum_gross_amount, maximum_gross_amount;

    std::string full_names[NUM_EMPLOYEES];
    double gross_pays[NUM_EMPLOYEES];

    std::ifstream infile;
    std::ofstream outfile;

    infile.open("C:\\Users\\Ayub\\OneDrive\\Desktop\\final_exam.txt");
    outfile.open("C:\\Temp\\payroll.txt");
    if (!infile.is_open())
    {
        std::cout << "Cannot open input file" << std::endl;
            exit(EXIT_FAILURE);
    }
    else if(!outfile.is_open())
    {
        std::cout << "Cannot open output file" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << std::fixed << std::setprecision(2);
    int sum = 0;

    input_full_name(infile, full_name);

    if (!infile.eof()) {

        show_header(outfile);
        do
        {
            input(infile, full_name, hours, hourly_rate, deduction);
            processing(gross_pay, hours, hourly_rate, taxes, net_pay,
                regular_hours, overtime_hours, deduction);
            output(outfile, full_name, hours, hourly_rate, gross_pay, taxes,
                net_pay, regular_hours, overtime_hours, deduction);
            full_names[sum] = full_name;
            gross_pays[sum] = gross_pay;
            input_full_name(infile, full_name);
            sum += 1;
        } while ((sum < NUM_EMPLOYEES) && (!infile.eof())); // 2nd !infile.eof

        std::cout
            << "The information was saved inside the"
            <<" file with the given address. :]"
            << std::endl << std::endl << std::endl;

        calculation(gross_pays, sum, total_gross_amount, average_gross_amount,
            minimum_gross_amount, maximum_gross_amount, full_names);
        summary_header(outfile);
        summary_output(outfile, total_gross_amount, average_gross_amount,
            minimum_gross_amount, maximum_gross_amount, sum, full_names,
            gross_pays);
    }
    else
    {
        std::cout <<
            "sorry, but it looks like you have a empty file."
            << " Please check your file again. :]"
        << std::endl << std::endl << std::endl;
    }
    infile.close();
    outfile.close();
}
//
// An input module that takes the person's hours,
// hourly_rate and deduction from the file.
//
void input(std::istream &stream, std::string& full_name, double& hours,
    double& hourly_rate, double &deduction)
{
    stream >> hours >> hourly_rate >> deduction;
}
//
// An input module that takes the person's first name and last and than
// concatenates these to create a full name in the form "First, Last".
//
void input_full_name(std::istream &stream, std::string &full_name)
{
    std::string first_name, last_name;
    stream >> last_name >> first_name;
    full_name = join_names(first_name, last_name);
}
//
// A sub processing function that concatenates the given first and last names
// to create a full name in the form "First, Last".
//
std::string join_names(std::string first_name, std::string last_name)
{
    std::string full_name;

    full_name = first_name + ", " + last_name;

    return full_name;
}
//
// A processing module that Calcultes the gross_pay, net_pay and taxes.
// By using the INFO from the file 'hours' and 'hourly_rate'.
//
void processing(double& gross_pay, double hours, double hourly_rate,
    double& taxes, double& net_pay, double& regular_hours,
    double& overtime_hours, double deduction)
{
    hours_spliter(hours, regular_hours, overtime_hours);
    gross_pay = full_gross_pay(hours, hourly_rate, regular_hours,
        overtime_hours);
    taxes = full_taxes(gross_pay);
    net_pay = full_net_pay(gross_pay, taxes, deduction);
}
//
// A sub processing module that splites the hours in regular hours and
// overtime hours, using hours which have been taken from the file.
//
void hours_spliter(double hours, double& regular_hours, double& overtime_hours)
{
    regular_hours = hours;

    if (hours <= OVERTIME)
    {
        overtime_hours = (regular_hours - hours);
    }
    else if (hours > OVERTIME)
    {
        overtime_hours = (hours - OVERTIME);
        regular_hours = (regular_hours - overtime_hours);
    }
}
//
// A sub processing function that Calcultes the gross_pay,
// By using the info from the file 'hours' and 'hourly_rate'.
//
double full_gross_pay(double hours, double hourly_rate,
    double regular_hours, double overtime_hours)
{
    double gross_pay;
    gross_pay = (regular_hours * hourly_rate) +
        (overtime_hours * (hourly_rate * 1.5));
    return gross_pay;
}
//
// A sub processing function that Calcultes the taxes,
// By using gross_pay and gross_percent and 'gross_percent' is a constant.
// 
double full_taxes(double gross_pay)
{
    double taxes;
    taxes = GROSS_PERCENT * gross_pay;
    return taxes;
}
//
// A sub processing function that Calcultes the net_pay,
// By using the gross_pay, taxes and parking which parking is also a constant.
//
double full_net_pay(double gross_pay, double taxes, double deduction)
{
    double net_pay;
    net_pay = gross_pay - taxes - deduction;
    return net_pay;
}
//
// This modules calls all the calculation and sorting modules, so it's clean.
//
void calculation(double gross_pays[], int count, double &total_gross_amount,
    double &average_gross_amount, double &minimum_gross_amount,
    double &maximum_gross_amount, std::string full_names[])
{
    total_gross_amount = total_gross_pay(gross_pays, count);
    average_gross_amount = average_gross_pay(gross_pays, count);
    minimum_gross_amount = minimum_gross_pay(gross_pays, count);
    maximum_gross_amount = maximum_gross_pay(gross_pays, count);
    descending_order(full_names, gross_pays, count);
}
//
// This function calculates the total gross pay of all the employees.
//
double total_gross_pay(double gross_pays[], int times)
{
    double total_gross_amount = 0.00;

    for (int i = 0; i < times; i++)
    {
        total_gross_amount += gross_pays[i];
    }
    return total_gross_amount;
}
//
// This function calculates the average gross pay of all the employees.
//
double average_gross_pay(double gross_pays[], int times)
{
    double average_gross_amount = 0.00;
    
    for (int i = 0; i < times; i++)
    {
        average_gross_amount += gross_pays[i];
    }
    return average_gross_amount / times;
}
//
// This function calculates the minimum gross pay of all the employees.
//
double minimum_gross_pay(double gross_pays[], int times)
{
    double minimum_gross_amount = 0.00;
    double min = gross_pays[0];

    for (int i = 0; i <= times-1; i++)
    {
        if ((gross_pays[i] <= gross_pays[i-1]))
        {
            min = gross_pays[i];
        }
    }
    return minimum_gross_amount = min;
}
//
// This function calculates the maximum gross pay of all the employees.
//
double maximum_gross_pay(double gross_pays[], int times)
{
    double maximum_gross_amount = 0.00;
    double max = gross_pays[0];

    for (int i = 0; i <= times-1; i++)
    {
        if ((gross_pays[i] >= gross_pays[i - 1]))
        {
            max = gross_pays[i];
        }
    }
    return maximum_gross_amount = max;
}
//
// This module is arranging the names and gross pay to descending order.
//
void descending_order(std::string full_names[], double gross_pays[], int times)
{
    bool swaps;        // flags if elements were swapped during a pass
    int  pass;         // pass counter
    int  i;            // general counter for comparing adjacent elements
    double  temp_number;  // facilitates swapping of adjacent array elements
    std::string temp_name;// facilitates swapping of adjacent array elements

    // this is used for the gross_pay sorting.
    swaps = true;
    for (pass = 1; (pass < times) && swaps; pass++) {
        swaps = false;
        for (i = 0; i < times - pass; i++) {
            if (gross_pays[i] < gross_pays[i + 1]) {
                swaps = true;
                temp_number = gross_pays[i];
                gross_pays[i] = gross_pays[i + 1];
                gross_pays[i + 1] = temp_number;
                temp_name = full_names[i];
                full_names[i] = full_names[i + 1];
                full_names[i + 1] = temp_name;
            }
        }
    }
}
//
//A output module that prints the information of hours, hourly rate and more to
// the file. This helps them not get lost or confuse about the numbers.
//
void show_header(std::ostream& stream)
{
    stream <<
        "                      reg    Ovt    Hourly  Gross               "
        << "     Net" << std::endl;
    stream <<
        "Name                  Hours  Hours  Rate    Pay      Taxes   Deduct"
        << "  Pay" << std::endl;
    stream <<
        "====================  =====  =====  ======  =======  ======  ======"
        << "  =======" << std::endl;
}
//
// This output module shows the header of the employee's summary.
//
void summary_header(std::ostream& stream)
{
    stream << std::endl << std::endl
        << "==============================" << std::endl
        << "   Employee Payroll Summary" << std::endl
        << "==============================";
    stream << std::endl << std::endl
        << "                      Gross" << std::endl
        << "Name                  Pay" << std::endl
        << "====================  ========" << std::endl;
}
//
// An output module that displays the results with person's full name.
// Also saves the information of the employees by sending it to a outside file.
//
void output(std::ostream& stream, std::string full_name, double hours,
    double hourly_rate, double gross_pay, double taxes, double net_pay,
    double regular_hours, double overtime_hours, double deduction)
{
    stream << std::fixed << std::setprecision(2);
    stream << std::left << std::setw(20) << full_name << "  ";
    stream << std::right << std::setw(5) << regular_hours << "  ";
    stream << std::right << std::setw(5) << overtime_hours << "  ";
    stream << std::right << std::setw(6) << hourly_rate << "  ";
    stream << std::right << std::setw(7) << gross_pay << "  ";
    stream << std::right << std::setw(6) << taxes << "  ";
    stream << std::right << std::setw(6) << deduction << "  ";
    stream << std::right << std::setw(7) << net_pay << "  "
        << std::endl;
}
//
// This output module prints the summary informations to the file.
//
void summary_output(std::ostream& stream, double total_gross_amount,
    double average_gross_amount, double minimum_gross_amount,
    double maximum_gross_amount, int sum, std::string full_names[],
    double gross_pays[])
{
    for (int i = 0; i < sum; i++)
    {
        stream << std::left << std::setw(20) << full_names[i] << "  ";
        stream << std::right << std::setw(8) << gross_pays[i] << std::endl;
    }
    stream << std::endl;
    stream << std::left << std::setw(20) << "Total Gross Pay" << "  ";
    stream << std::right << std::setw(8) << total_gross_amount << std::endl;
    stream << std::left << std::setw(20) << "Average Gross Pay" << "  ";
    stream << std::right << std::setw(8) << average_gross_amount << std::endl;
    stream << std::left << std::setw(20) << "Minimum Gross Pay" << "  ";
    stream << std::right << std::setw(8) << minimum_gross_amount << std::endl;
    stream << std::left << std::setw(20) << "Maximum Gross Pay" << "  ";
    stream << std::right << std::setw(8) << maximum_gross_amount << std::endl;
}