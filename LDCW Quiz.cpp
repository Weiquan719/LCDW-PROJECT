#include <iostream>  
#include <vector>   
#include <string>  
#include <limits>   
#include <fstream>  
#include <cctype>    


struct Question {
    std::string text;
    std::vector<std::string> options;
    char correctAnswer; 
    std::string citation; 
};

// Function to validate student ID (10 digits, numeric)
bool validateStudentId(const std::string& id) {
    if (id.length() != 10) {
        return false;
    }
    for (int i = 0; i < id.length(); i++) { 
        if (!isdigit(id[i])) {
            return false;
        }
    }
    return true;
}


char toLower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + 32;  
    }
    return c;
}


char askQuestion(const std::string& question, const std::vector<std::string>& options, char correctAnswer) {
    char answer;
    std::cout << question << std::endl;
    for (char optChar = 'a'; optChar < 'a' + options.size(); optChar++) {
        std::cout << optChar << ") " << options[optChar - 'a'] << std::endl;
    }
    std::cout << std::endl; // Add an empty line after each question and options

    bool validInput = false;
    while (!validInput) {
        std::cout << "Your answer (a, b, c, or d): ";
        std::cin >> answer;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

        answer = toLower(answer); 

        if (answer >= 'a' && answer < 'a' + options.size()) {
            validInput = true;
        } else {
            std::cout << "Invalid input. Please enter 'a', 'b', 'c', or 'd'." << std::endl;
        }
    }
    return answer;
}

// Function to get the text for the user's chosen answer
std::string getAnswerText(char answer, const std::vector<std::string>& options) {
    if (answer >= 'a' && answer < 'a' + options.size()) {
        return options[answer - 'a'];
    }
    return "";
}

// Function to save results to a text file
void saveResultsToFile(const std::string& name, const std::string& studentId, const std::vector<Question>& questions,
                       const std::vector<char>& userAnswers, int score) {
    // Use append mode to keep old results and add new ones
    std::string filename = "result of quiz ldcw.txt";
    std::ofstream outFile(filename.c_str(), std::ios::app);  // Open in append mode

    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return;
    }

    outFile << "\n--- Quiz Results ---\n" << std::endl;
    outFile << "Name: " << name << std::endl;
    outFile << "Student ID: " << studentId << std::endl;
    outFile << "Final Score: " << score << " out of 10" << std::endl;
    outFile << "\n--- Questions and Answers ---\n" << std::endl;

    for (int i = 0; i < questions.size(); ++i) {
        outFile << "Question " << (i + 1) << ": " << questions[i].text << std::endl;
        for (char optChar = 'a'; optChar < 'a' + questions[i].options.size(); ++optChar) {
            outFile << "  " << optChar << ") " << questions[i].options[optChar - 'a'] << std::endl;
        }

        outFile << "  Your Answer: " << getAnswerText(userAnswers[i], questions[i].options) << std::endl;
        outFile << "  Correct Answer: " << getAnswerText(questions[i].correctAnswer, questions[i].options) << std::endl;
        outFile << std::endl; // Add space between questions for better readability
    }

    outFile.close();
    std::cout << "\nQuiz results saved to " << filename << std::endl;
}

int main() {
    std::string name;
    std::string studentId;
    std::vector<char> userAnswers(10); // Store user answers
    int score = 0;

    std::cout << "Welcome to the Smart Energy Knowledge Quiz!" << std::endl;
    std::cout << "This quiz will test your understanding of Smart Grids, Smart Cities, and Energy Efficiency." << std::endl;
    std::cout << std::endl;  // Add a blank line for better readability

    // Get user name and validate student ID
    std::cout << "Please enter your name: ";
    std::getline(std::cin, name);
    std::cout << std::endl;  // Add a blank line after name input

    bool validId = false;
    while (!validId) {
        std::cout << "Please enter your 10-digit student ID (e.g., 1211202337): ";
        std::cin >> studentId;
        std::cin.ignore(10000, '\n'); // Clear buffer

        if (validateStudentId(studentId)) {
            validId = true;
        } else {
            std::cout << "Invalid Student ID. It must be exactly 10 digits and contain only numbers." << std::endl;
        }
        std::cout << std::endl;  // Add a blank line after ID input
    }

    // Define the quiz questions and answers
    std::vector<Question> questions;
    
    // Initialize questions manually without list initialization
    Question q1;
    q1.text = "1. What percentage of global greenhouse gas emissions do cities account for?";
    q1.options.push_back("A) Nearly 50%");
    q1.options.push_back("B) Nearly 60%");
    q1.options.push_back("C) Nearly 75%");
    q1.options.push_back("D) Nearly 80%");
    q1.correctAnswer = 'd';
    questions.push_back(q1);

    Question q2;
    q2.text = "2. In the context of the energy trilemma, which three objectives need to be balanced?";
    q2.options.push_back("A) Innovation, Cost, Security");
    q2.options.push_back("B) Sustainability, Security, Affordability");
    q2.options.push_back("C) Efficiency, Growth, Environment");
    q2.options.push_back("D) Technology, Policy, Society");
    q2.correctAnswer = 'b';
    questions.push_back(q2);

    // Add more questions manually
    Question q3;
    q3.text = "3. How many key Smart Grid components in the intersection with Smart Cities are identified in the paper?";
    q3.options.push_back("A) 10");
    q3.options.push_back("B) 11");
    q3.options.push_back("C) 16");
    q3.options.push_back("D) 22");
    q3.correctAnswer = 'c';
    questions.push_back(q3);

    Question q4;
    q4.text = "4. What is AMI (Advanced Metering Infrastructure) primarily known for in Smart Grids?";
    q4.options.push_back("A) Long-distance power transmission");
    q4.options.push_back("B) Real-time two-way information exchange between grid and consumer");
    q4.options.push_back("C) Physical security of substations");
    q4.options.push_back("D) Hydropower generation");
    q4.correctAnswer = 'b';
    questions.push_back(q4);

    Question q5;
    q5.text = "5. Which of the following is mentioned as one of the challenges in smart grid implementation?";
    q5.options.push_back("A) Low investment costs");
    q5.options.push_back("B) High level of public awareness");
    q5.options.push_back("C) Interoperability issues");
    q5.options.push_back("D) Abundance of standardized technologies");
    q5.correctAnswer = 'c';
    questions.push_back(q5);

    Question q6;
    q6.text = "6. What percentage of overall energy and overall trade-related greenhouse gas emissions are cities responsible for?";
    q6.options.push_back("A) Around 50%");
    q6.options.push_back("B) Around 65%");
    q6.options.push_back("C) Around 75%");
    q6.options.push_back("D) Around 85%");
    q6.correctAnswer = 'c';
    questions.push_back(q6);

    Question q7;
    q7.text = "7. How is IoE (Internet of Energy) described in relation to providing sustainable energy management towards a green city?";
    q7.options.push_back("A) A complex obstacle");
    q7.options.push_back("B) A revolutionary technology");
    q7.options.push_back("C) A traditional power source");
    q7.options.push_back("D) A limited data source");
    q7.correctAnswer = 'b';
    questions.push_back(q7);

    Question q8;
    q8.text = "8. Which three specific functions do energy storage technologies contain, as mentioned in IoE-based smart power systems?";
    q8.options.push_back("A) Low-frequency rate, low significance, high energy reliability");
    q8.options.push_back("B) Timely changing of bulk energy, rate of recurrence within low range, regularity solidity within high significance");
    q8.options.push_back("C) High-frequency rate, high significance, low energy reliability");
    q8.options.push_back("D) Static energy, fixed tariff, limited reliability");
    q8.correctAnswer = 'b';
    questions.push_back(q8);

    Question q9;
    q9.text = "9. What is a Smart Grid defined as?";
    q9.options.push_back("A) An electricity network with only one-way power flow");
    q9.options.push_back("B) A system solely for traditional fossil fuel power plants");
    q9.options.push_back("C) An electricity grid equipped with advanced communication, automation, and IT systems enabling real-time bidirectional monitoring and control of electricity and information");
    q9.options.push_back("D) A network primarily for manual control and monitoring");
    q9.correctAnswer = 'c';
    questions.push_back(q9);

    Question q10;
    q10.text = "10. Which of the following is a benefit of Smart Grids mentioned in the paper?";
    q10.options.push_back("A) Increased operational costs for utilities");
    q10.options.push_back("B) Reduced integration of large-scale renewable energy systems");
    q10.options.push_back("C) Facilitates quicker restoration of electricity in case of power supply disturbances");
    q10.options.push_back("D) Decreased energy security due to decentralization");
    q10.correctAnswer = 'c';
    questions.push_back(q10);

    
    for (int i = 0; i < 10; ++i) {
        userAnswers[i] = askQuestion(questions[i].text, questions[i].options, questions[i].correctAnswer);
        std::cout << std::endl;  // Add a blank line after each question to make it clearer
    }

    
    int option;
    while (true) {
        std::cout << "\nChoose an option:\n";
        std::cout << "1. Do you need to reselect an answer?\n";
        std::cout << "2. Print the result\n";
        std::cin >> option;

       
        if (std::cin.fail() || (option != 1 && option != 2)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid option. Please choose 1 or 2.\n";
        } else {
            if (option == 1) {
                int questionNumber;
                std::cout << "Enter the question number to reselect: ";
                std::cin >> questionNumber;
                if (questionNumber >= 1 && questionNumber <= 10) {
                    userAnswers[questionNumber - 1] = askQuestion(questions[questionNumber - 1].text, questions[questionNumber - 1].options, questions[questionNumber - 1].correctAnswer);
                } else {
                    std::cout << "Invalid question number.\n";
                }
            } else if (option == 2) {
                
                for (int i = 0; i < 10; ++i) {
                    if (userAnswers[i] == questions[i].correctAnswer) {
                        score++;
                    }
                }

                std::cout << "\nQuiz Results Summary\n";
                std::cout << "Your Final Score: " << score << " out of 10\n";
                
                for (int i = 0; i < 10; ++i) {
                    std::cout << "Question " << (i + 1) << ": " << questions[i].text << std::endl;
                    std::cout << "  Your Answer: " << getAnswerText(userAnswers[i], questions[i].options) << std::endl;
                    std::cout << "  Correct Answer: " << getAnswerText(questions[i].correctAnswer, questions[i].options) << std::endl;
                    std::cout << std::endl;
                }

                saveResultsToFile(name, studentId, questions, userAnswers, score);
                break; // 退出 option loop，进入下一步
            }
        }
    }

    while (true) {
        int finalChoice;
        std::cout << "\nWhat would you like to do next?\n";
        std::cout << "1. Redo the quiz\n";
        std::cout << "2. Exit the program\n";
        std::cout << "Enter your choice (1 or 2): ";
        std::cin >> finalChoice;

        if (std::cin.fail() || (finalChoice != 1 && finalChoice != 2)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter 1 or 2 only.\n";
        } else {
            if (finalChoice == 1) {
                std::cout << "\nRestarting the quiz...\n\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				main(); // 重新启动程序
                return 0;
            } else if (finalChoice == 2) {
                std::cout << "\nThank you for participating. Goodbye!\n";
                break;
            }
        }
    }

    return 0;
}
