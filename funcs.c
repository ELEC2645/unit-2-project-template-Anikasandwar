#include <stdio.h>
#include "funcs.h"
#include <ctype.h>
#include <string.h>
#include <math.h>
//ASCII Graph for the charging and discharging 
#define MAX_POINTS 30   // number of time steps
#define GRAPH_HEIGHT 10 // rows in graph
#define GRAPH_WIDTH 40  // columns in graph


void menu_item_1(void){
    resistor_network_menu();
}
// Resistor network submenu 
void resistor_network_menu(void)
{
    int choice; //define the variable choice
// submenu 
    printf("\n=========== RESISTOR NETWORK ANALYSIS ===========\n");
    printf("1. Series Resistance\n");
    printf("2. Parallel Resistance\n");
    printf("3. Mixed/Combined Network analysis\n");
    printf("4. Back to Main Menu\n");
    printf("Select: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            calc_series();
            break;
        case 2:
            calc_parallel();
            break;
        case 3:
            calc_mixed(); // a mixture of series and parallel resistances to be calculated 
            break;
        default:
            return;  // go back to main menu //
    }
}
// Series resistance calculation 
// R total = R1+R2+R3...
void calc_series(void) {
    int n;
    printf("\nHow many resistors in series? "); // user inputs 
    scanf("%d", &n); // read the user input
    // if the user enters a negative value (error handling)
    if (n<=0){
        printf("Invalid number of resistors, returning to the main menu");
        return;
    }

    scanf("%d", &n);

    double resistors[n];    // creates an array to store resistor values
    double total = 0;

    for (int i = 0; i < n; i++) {  // loop through array until the value that the user specified is reached
        printf("Enter R%d (ohms): ", i + 1);
        scanf("%lf", &resistors[i]);
        // error handling 
        if (resistors[i] < 0) {
            printf("warning, resistor value cannot be negative.\n");
        }
        total += resistors[i];  // total series resistance 
    }

    printf("\nTotal series Resistance = %.3f ohms\n", total); // 3 decimal places 
}
// Parallel resistance calculation
// 1/R_total = 1/R1 + 1/R2 + ...
void calc_parallel(void) {
    int n;
    printf("\nHow many resistors in parallel? ");
    scanf("%d", &n);
    // if the user enters a negative value (error handling)
    if (n<=0){
        printf("Invalid number of resistors, returning to the main menu");
        return;
    }

    double resistors[n];   // array to store resistor values
    double inv_sum = 0;

    for (int i = 0; i < n; i++) { //for loop
        printf("Enter R%d (ohms): ", i + 1);
        scanf("%lf", &resistors[i]);
        //error handling 
        if (resistors[i] <= 0) {
            printf("warning, the resistance cannot be negative.\n");
        }
        inv_sum += 1.0 / resistors[i];  // calculate the total parallel resistance 
    }

    double total = 1.0 / inv_sum;
    printf("\nTotal parallel Resistance = %.3f ohms\n", total); // 3 decimal places 
}
// mixed calculations 
void calc_mixed(void) {
    printf("\n--- Mixed Network Calculator ---\n"); // multiple series and parallel connections 
    // series resistance 
    int n_series;
    printf("How many series resistors? ");
    scanf("%d", &n_series);
    // if the user enters a negative value (error handling)
    if (n_series<=0){
        printf("Invalid number of resistors, returning to the main menu");
        return;
    }
    double series[n_series];
    double series_total = 0;
    for (int i = 0; i < n_series; i++) { // for loop 
        printf("Enter series R%d (ohms): ", i + 1);
        scanf("%lf", &series[i]);
        if (series[i] < 0) {
            printf("warning, the resistance cannot be in negative, try again.\n"); // error handling 
        }
        series_total += series[i];
    }
    printf("Series group total = %.3f ohms\n", series_total);
    // parallel part
    int n_parallel;
    printf("How many parallel resistors? ");
    scanf("%d", &n_parallel);
    // if the user enters a negative value (error handling)
    if (n_parallel<=0){
        printf("Invalid number of resistors, returning to the main menu");
        return;
    }
    double parallel[n_parallel];
    double inv_sum = 0;
    for (int i = 0; i < n_parallel; i++) {
        printf("Enter parallel R%d (ohms): ", i + 1);
        scanf("%lf", &parallel[i]);
        if (parallel[i] <= 0) { // error handling 
            printf("warning, the resistance cannot be in negative, try again.\n");
        }
        inv_sum += 1.0 / parallel[i];
    }
    double parallel_total = 1.0 / inv_sum;
    printf("Parallel group total = %.3f ohms\n", parallel_total);

    // total combined resistance
    double total = series_total + parallel_total;
    printf("\n The final combined Resistance = %.3f ohms\n", total); // the total resistance 
}
//Menu item 2, voltage/current/power calculations
void menu_item_2(void) {
    voltage_power_current(); 
}
// Submenu 
void voltage_power_current(void){
    int choice; 
    char explain; 
    printf("=======voltage/current/power calculator=======\n");
    printf("1. Calculate Voltage (V = I * R)\n");
    printf("2. Calculate Current (I = V / R)\n");
    printf("3. Calculate Power (P = V * I)\n");
    printf("4. Auto Solver (enter any 2 values, find 3rd)\n");
    printf("5. Explanation of the formulas\n");
    printf("6. Back to Main Menu\n");
    printf("Select: ");
    scanf("%d", &choice);
    switch(choice) {
        case 1:
            calculate_voltage();
            break;
        case 2:
            calculate_current();
            break;
        case 3:
            calculate_power();
            break;
        case 4:
            auto_solver();
            break;
        case 5:
            Formula_explanation();
            break;
        default:
            return;
    }
}
// explanation of the formulas 
void Formula_explanation(void) {
    printf("\n--- Explanation of Basic Electrical Formulas ---\n");
    FILE* input = fopen("explanations.txt","r");
    if (!input) {
        printf("Error: The file 'explanations.txt' cannot be opened. Ensure it exists.\n");
        return;   
    }
    char line[512];
    while(fgets(line, sizeof(line), input)){
        printf("%s", line);
    }
    fclose(input);
    printf("--- End of Explanations ---\n");
   }

// Calculate Voltage: V = I * R
void calculate_voltage(void) {
    double I, R;
    printf("\nEnter Current (I in Amps): ");
    scanf("%lf", &I);
    printf("Enter Resistance (R in Ohms): ");
    scanf("%lf", &R);

    if (I < 0 || R < 0) {
        printf("Error values must be positive.\n");
        return;
    }
    double V = I * R;
    printf("Voltage V = %.3f V\n", V);
}
// Calculate Current: I = V / R
void calculate_current(void) {
    double V, R;
    printf("\nEnter Voltage (V in Volts): ");
    scanf("%lf", &V);
    printf("Enter Resistance (R in Ohms): ");
    scanf("%lf", &R);
    if (R <= 0 || V<0 ) {
        printf("Error, resistance and voltage must be greater than 0\n");
        return;
    }
    double I = V / R;
    printf("Current I = %.3f A\n", I);
}
// Calculate Power: P = V * I
void calculate_power(void) {
    double V, I;
    printf("\nEnter Voltage (V in Volts): ");
    scanf("%lf", &V);
    printf("\nEnter Current (I in Amps): ");
    scanf("%lf", &I);
    if (V < 0 || I < 0) {
        printf("Error, voltage and current cannot be negative\n");
        return;
    }
    double P = V * I;
    printf("Power P = %.3f W\n", P);
}
// AUTO SOLVER
void auto_solver(void){
    double V = 0, I = 0, R = 0, P = 0;
    char first, second;
    printf("====Auto solver: enter any 2 values and the third is calculated====\n");
    printf("Choose first known value (V/I/R/P): ");
    scanf(" %c", &first);
    first = toupper(first);
    printf("Choose second known value (V/I/R/P): ");
    scanf(" %c", &second);
    second = toupper(second);
    // Input values
    if (first == 'V') { printf("Enter Voltage (V): "); scanf("%lf", &V); }
    if (first == 'I') { printf("Enter Current (A): "); scanf("%lf", &I); }
    if (first == 'R') { printf("Enter Resistance (Ohms): "); scanf("%lf", &R); }
    if (first == 'P') { printf("Enter Power (W): "); scanf("%lf", &P); }

    if (second == 'V') { printf("Enter Voltage (V): "); scanf("%lf", &V); }
    if (second == 'I') { printf("Enter Current (A): "); scanf("%lf", &I); }
    if (second == 'R') { printf("Enter Resistance (Ohms): "); scanf("%lf", &R); }
    if (second == 'P') { printf("Enter Power (W): "); scanf("%lf", &P); }

    if (V == 0) {
        if (I != 0 && R != 0) V = I * R;
        else if (P != 0 && I != 0) V = P / I;
    }
    if (I == 0) {
        if (V != 0 && R != 0) I = V / R;
        else if (P != 0 && V != 0) I = P / V;
    }
    if (R == 0) {
        if (V != 0 && I != 0) R = V / I;
    }
    if (P == 0) {
        if (V != 0 && I != 0) P = V * I;
    }
    // Print results
    printf("\n===== RESULTS =====\n");
    printf("Voltage (V): %.3f V\n", V);
    printf("Current (I): %.3f A\n", I);
    printf("Resistance (R): %.3f Ohms\n", R);
    printf("Power (P): %.3f W\n", P);
    if (P > 1000) {
        printf("\n WARNING: Power exceeds safe limit (1000W)!\n");
    }
}
void menu_item_3(void){
    RC_circuit_analyser();
}
//Submenu 
void RC_circuit_analyser(void){
    int choice;
    printf("=====RC circuit analytics=====\n");
    printf("1.Charging simulation\n");
    printf("2.Discharging simulation\n");
    printf("3.Visual of the recent graphs generated on Excel\n");
    printf("4.Back to Main menu\n");
    printf("Select: ");
    scanf("%d", &choice);
    switch(choice){
        case 1:
            Charging_simulation();
            break;
        case 2:
            Discharging_simulation();
            break;
        case 3:
            Graph_visuals();
            break;
        default:
            return;
    }
}
void Charging_simulation(void) {
    double R = 0, C = 0, Vsup = 0; // initialize
    // Ask user for inputs with error checking
    while (R <= 0) {
        printf("Enter Resistance R (Ohms): ");
        scanf("%lf", &R);
        if (R <= 0) printf("Error, try again\n");
    }
    while (C <= 0) {
        printf("Enter Capacitance C: ");
        scanf("%lf", &C);
        if (C <= 0) printf("Error, try again\n");
    }
    while (Vsup <= 0) {
        printf("Enter Supply Voltage V: ");
        scanf("%lf", &Vsup);
        if (Vsup <= 0) printf("Error, try again\n");
    }
    double tau = R * C;
    double t_max = 5 * tau;
    double t_step = t_max / MAX_POINTS;
    double time[MAX_POINTS + 1];
    double voltage[MAX_POINTS + 1];
    // calculate voltage over time
    for (int i = 0; i <= MAX_POINTS; i++) {
        time[i] = i * t_step;
        voltage[i] = Vsup * (1.0 - exp(-time[i] / tau));
        printf("t=%.2fs, V=%.2fV\n", time[i], voltage[i]);
    }
    // ASCII Graph
    printf("\n== Capacitor Charging graph ==\n");
    printf("Voltage(V) 0V to %.2fV\n", Vsup);
    printf("\t--------------------------------------->\n");
    // Loop through all the data points
    for (int i = MAX_POINTS; i >= 0; i--) {
        // voltage ratio
        double volt_ratio = voltage[i] / Vsup; // voltage divide it by the max voltage for the ratio
        int position = (volt_ratio * 40); // compared with the graph width 
        // printing the label 
        printf("%.2fv  |", voltage[i]);
        // Print the spaces 
        for (int j = 0; j < position; j++) {
             printf(" "); 
        }
        //  Print the data points on the graph 
        printf("*\n");
    }
    printf("\t---------------------------------------> Time (s)\n");
     // End of Charging_simulation function
    // Save CSV
    FILE *f = fopen("simulation.csv", "a"); //at first i used "w" instead of "a" and when i used that then if i did another charging simulation then the old one would dissapear so i changed it to "a" and that doesn't happen 
    fprintf(f, "\n===charging Data===\n");
    fprintf(f, "Time (s),Voltage (V)\n");
    if (!f) {
        printf("Could not open file!\n");
        return;
    }
    for (int i = 0; i <= MAX_POINTS; i++) {
        fprintf(f, "%.2f,%.2f\n", time[i], voltage[i]);
    }
    fclose(f);
    // The most recent data to plot the graph in excel
    printf("Data of the charging simulation is stored in simulation.csv\n");
    // Saving CSV to plot in excel 
    FILE *f_excel = fopen("last_simulation.csv", "w");
    if (f_excel) {
        fprintf(f_excel, "Time(s),Voltage(V)\n");
        for (int i = 0; i <= MAX_POINTS; i++) {
            fprintf(f_excel, "%.2f,%.2f\n", time[i], voltage[i]);
    }
    fclose(f_excel);
    printf("Simulation exported to last_simulation.csv — open in Excel for graph.\n");
}
}
void Discharging_simulation(void) {
    double R = 0, C = 0, Vint = 0; // initialize

    // Ask the user for inputs with error checking
    while (R <= 0) {
        printf("Enter Resistance R (Ohms): ");
        scanf("%lf", &R);
        if (R <= 0) printf("Error, try again\n");
    }
    while (C <= 0) {
        printf("Enter Capacitance C: ");
        scanf("%lf", &C);
        if (C <= 0) printf("Error, try again\n");
    }
    while (Vint <= 0) {
        printf("Enter initial Voltage V: ");
        scanf("%lf", &Vint);
        if (Vint <= 0) printf("Error, try again\n");
    }

    double tau = R * C;
    double t_max = 5 * tau;
    double t_step = t_max / MAX_POINTS;
    double time[MAX_POINTS + 1];
    double voltage[MAX_POINTS + 1];

    // Calculate voltage over time
    for (int i = 0; i <= MAX_POINTS; i++) {
        time[i] = i * t_step;
        voltage[i] = Vint * exp(-time[i] / tau);
        printf("t=%.2fs, V=%.2fV\n", time[i], voltage[i]);
    }
    // ASCII graph
    printf("\n=== graph for discharging ===\n");
    printf("Voltage(v) 0V to %.2fV)\n",Vint);
    printf("\t--------------------------------------->\n");
    //loop through all the data points 
    for (int i = MAX_POINTS; i >= 0; i--) {
        // voltage ratio
        double volt_ratio = voltage[i] / Vint; // voltage divide it by the max voltage for the ratio
        int position = (volt_ratio * 40); // compared with the graph width 
        // printing the label 
        printf("%.2fv  |", voltage[i]);
        // Print the spaces 
        for (int j = 0; j < position; j++) {
             printf(" "); 
        }
        //  Print the data points on the graph 
        printf("*\n");
    }
    printf("\t---------------------------------------> Time (s)\n");
    // Save to main CSV (append)
    FILE *f = fopen("simulation.csv", "a");
    if (!f) {
        printf("Could not open simulation.csv!\n");
        return;
    }
    fprintf(f, "\n===Discharging Data ===\n");
    fprintf(f, "time(s),voltage(V)\n");
    for (int i = 0; i <= MAX_POINTS; i++) {
        fprintf(f, "%.3f,%.3f\n", time[i], voltage[i]);
    }
    fclose(f);

    // Save to Excel CSV 
    FILE *f_excel = fopen("last_simulation.csv", "w");
    if (f_excel) {
        fprintf(f_excel, "Time(s),Voltage(V)\n");
        for (int i = 0; i <= MAX_POINTS; i++) {
            fprintf(f_excel, "%.2f,%.2f\n", time[i], voltage[i]);
        }
        fclose(f_excel);
        printf("Simulation exported to last_simulation.csv — open in Excel for graph.\n");
    } else {
        printf("Could not create last_simulation.csv!\n");
    }
}
// The most recent data will be plotted on excel
void Graph_visuals(void){
    FILE*f_excel = fopen("last_simulation.csv","r");
    printf("Simulation exported to last_simulation.csv — open in Excel.\n");
}
void menu_item_4(void){
    unit_converter_menu();
}
//Submenu 
void unit_converter_menu(void) {
    int choice;
    printf("=======Engineering Unit Converter=======\n");
    printf("1. Metric Prefix Conversion\n");
    printf("2. Decibel (dB) Conversions\n");
    printf("3. Back to Main Menu\n");
    printf("Select: ");
    scanf("%d", &choice);
    switch(choice) {
        case 1:
        metric_conversion_menu();
        break;
        case 2:
        dB_conversion_menu();
        break;
        case 3:
        break;
        default:
        return;
    }
}
void metric_conversion_menu(void)
{
    struct metric_conversion {
    char conversion[3];
    double value;
};
    struct metric_conversion list[] = {
        {"k", 1e3},
        {"M", 1e6},
        {"G", 1e9},
        {"m", 1e-3},
        {"u", 1e-6},
        {"n", 1e-9},
        {"p", 1e-12},
        {"", 1} //no value, base 
    };
    int count = sizeof(list)/sizeof(list[0]);
    char input_convert[3];
    char output_convert[3];
    double value; //original value
    double converted_value; // temporaty stored
    double final_value; // final value 
    printf("\n=== Metric Conversion ===\n");
    printf("Available: k  M  G  m  u  n  p\n");
    printf("Convert from: ");
    scanf("%s", input_convert);
    printf("Value to convert: ");
    scanf("%lf", &value);
    printf("Convert to: ");
    scanf("%s", output_convert);
    struct metric_conversion *ptr = list;
    int i = 0;
    double input_value = 0, output_value = 0; // initialize 
    while (i < count) {
        if (strcmp(input_convert, ptr->conversion) == 0) { // check the two strings 
        input_value = ptr->value;
    }
    if (strcmp(output_convert, ptr->conversion) == 0) {
        output_value = ptr->value;
    }
    ptr++;  // move pointer moves to the next element
    i++;    // increment counter
}
// error handing 
    if (input_value == 0 || output_value == 0){
        printf("Invalid\n");
        return;
    }
// formula for conversion 
final_value = ((value * input_value)/output_value);
printf("%.3f\n", final_value);
}
//Decible (db) conversions 
void dB_conversion_menu(void) {
    int choice;
    printf("====dB conversion menu\n");
    printf("1. dB to voltage ratio\n");
    printf("2. dB to power ratio\n");
    printf("3. Voltage ratio to dB\n");
    printf("4. Power ratio to dB\n");
    printf("5. Back to Unit Converter Menu\n");
    printf("Select: ");
    scanf("%d", &choice);
    switch(choice){
        case 1:
        dB_to_voltage();
        break;
        case 2:
        dB_to_power();
        break;
        case 3:
        voltage_to_dB();
        break;
        case 4:
        Power_to_dB();
        break;
        default:
        return;
    }
}
void dB_to_voltage(void) { 
    double dB;
    printf("Enter dB: ");
    scanf("%lf", &dB);
    double ratio = pow(10, dB / 20);
    printf("Voltage ratio = %.3f\n", ratio);
}
void dB_to_power(void) {
    double dB;
    printf("Enter dB: ");
    scanf("%lf", &dB);
    double ratio = pow(10, dB / 10);
    printf("Power ratio = %.3f\n", ratio);
}
void voltage_to_dB(void) {
    double Vin = 0, Vout = 0; // initialize the values 
    while (Vin <= 0) { // check for error
        printf("Enter Vin: ");
        if (Vin<=0){
            printf("Error, check your values again");
        }
        scanf("%lf", &Vin);
    }
    while (Vout <= 0) {
        printf("Enter Vout: ");
        if (Vout<=0){
            printf("Error,check the values again");
        }
        scanf("%lf", &Vout);
    }
    // Calculate dB
    double dB = 20 * log10(Vout / Vin);
    printf("Value in dB: %.2f dB\n", dB); // 2 decimal places
}
void Power_to_dB(void) {
    double Pin = 0, Pout = 0;
    // Input Pin
    while (Pin <= 0) {
        printf("Enter Pin: ");
        scanf("%lf", &Pin);
        if (Pin <= 0) {
            printf("Error, check values\n");
        }
    }
    // Input Pout
    while (Pout <= 0) {
        printf("Enter Pout: ");
        scanf("%lf", &Pout);
        if (Pout <= 0){
            printf("Error, check values\n");
        } 
    }
    double dB = 10 * log10(Pout / Pin);
    printf("Power ratio in dB: %.2f dB\n", dB);
}
void menu_item_5(void) { //Basic circuit theory help 
     Basic_circuit_theory();
}
//Submenu 
void Basic_circuit_theory(){
    int choice;
    printf("=====Circuit theory helper=====\n");
    printf("1.Commonly asked questions for RC circuits\n");
    printf("2.Commonly asked theorems\n");
    printf("3.Commonly asked power and energy questions\n");
    printf("4.A generic quiz to test your knowledge\n");
    printf("5.Back to main menu\n");
    printf("Select: ");
    scanf("%d", &choice);
    switch(choice){
        case 1: 
        RC_circuit();
        break;
        case 2:
        Theorems();
        break;
        case 3:
        Power_Energy();
        break;
        case 4:
        Quiz();
        break;
        default:
        return;
    }
}
void RC_circuit(){
    FILE *file = fopen("rcquestions.txt", "r");
    if (!file) {
        printf("Could not open file\n");
        return;
    }
    char line[1000]; // buffer for each line
    printf("\n===== RC Circuit Questions =====\n\n");

    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}
void Theorems(){
    FILE *file = fopen("Theorems.txt", "r");
    if (!file) {
        printf("Could not open file\n");
        return;
    }
    char line[1000]; // buffer for each line
    printf("\n===== commonly asked theorems =====\n");

    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
}
void Power_Energy(){
    FILE *file = fopen("Power_Energy.txt", "r");
    if (!file) {
        printf("Could not open file\n");
        return;
    }
    char line[1000]; // buffer for each line
    printf("\n=====Commonly asked power and energy questions=====\n");

    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
}
// Quiz to test your knowledge 
struct Question{
    char question[400];
    char total_options[4][200]; // user has 4 options to pick from
    int correct_option;
};
// total 5 questions questions 
struct Question quiz[] = {
    { 
        "What is the impedance of a capacitor?",
        { "1/jwC", "jwC", "R", "None" },
        1
    },
    {   
         "In an RC charging circuit, the voltage across the capacitor is given by:",
        { "V(1 - e^(-t/RC))",
          "V e^(-t/RC)",
          "Vt / RC",
          "(V/RC) e^(-t/RC)" },
        1
    },
    {   
        "The time constant of an RC circuit represents:",
        { "The time to fully charge the capacitor",
          "The time to charge to 50% of the supply voltage",
          "The time to reach about 63% of the final voltage",
          "The time to discharge completely" },
        3
    },
    {   
        "A 10 Ω resistor and 5 Ω resistor are connected in series across a 30 V supply.\nWhat is the voltage across the 10 Ω resistor?",
        { "5 V", "10 V", "15 V", "20 V" },
        3
    },
    {  
        "Power in an electrical circuit is given by which expression?",
        { "P = VI", "P = V/I", "P = I/R", "P = VR" },
        1
    },
    {   
        "A capacitor of 20 µF is charged through a 2 kΩ resistor. What is the time constant?",
        { "0.01 s", "0.04 s", "0.2 s", "0.4 s" },
        2
    }
};
void Quiz(void){
    int score = 0; // initialize 
    int answer;
    printf("====Circuit theory quiz! Test your knowledge=====\n");
    int i = 0;
    int total_questions = 5;

    while (i < (sizeof(quiz)/sizeof(quiz[0]))) {
        // print question
        printf("\nQ%d) %s\n", i + 1, quiz[i].question);
        // print all 4 options 
        int j=0;
        while(j<4){
            printf("%d) %s\n",j+1,quiz[i].total_options[j]);
            j++;
        }
        //ask the user for the input 
        answer = 0; // initialize 
        while (answer < 1 || answer > 4) { // error handling
            printf("Answer (1-4): ");
            scanf("%d", &answer);  

            if (answer < 1 || answer > 4) {
                printf("Invalid! Pick 1, 2, 3, or 4.\n");
            }
        }
        //check if correct 
        if (answer == quiz[i].correct_option){
            printf("correct answer!\n");
            score++;
        }
        else{
            printf("Wrong! the correct answer was: %d\n", quiz[i].correct_option);
        }
        i++; // loop continues to the next question 
    } 
    // end of quiz 
    printf("\n=====quiz results=====\n");
    printf("You scored %d out of %d\n", score, total_questions);
    //adding a highscore system using file handling 
    FILE *f =fopen("highscore.txt", "r");
    if (!f){
        printf("Could not open the file!\n");
        return;
    }
    int highscore = 0; // initialize 
    fscanf(f, "%d", &highscore);
    fclose(f);
    // compare scores 
    if (score>highscore){
        printf("YAY! NEW HIGH SCORE!\n");
        //write the updated score 
        f = fopen("highscore.txt","w");
        if (f){
            fprintf(f,"%d",score);
            fclose(f);
        }
    }
    else{
        printf("highscore is still:%d\n", highscore);
    }
    printf("\nReturning to main menu\n");
}
