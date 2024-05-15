// INCOMPLETE
#include <iostream>
#include <curl/curl.h>
#include <string>
#include <chrono>
#include <thread>

size_t writeCallback(void *ptr, size_t size, size_t nmemb, std::string *data) {
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

template<typename Function>
void wait(int seconds, Function currentFunction) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
    currentFunction();
}


#include <iostream>
#include <curl/curl.h>
#include <string>
#include <algorithm>

int startdcwf();

int send_request(std::string url) {
    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return res;
}

void send_whdel_req(const std::string& url) {
    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "Webhook successfully nuked. (Deleted)" << std::endl;
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    startdcwf();
}

void webhook_spam(std::string url) {
    std::string content;
    std::cout << "Spam Message: ";
    std::getline(std::cin, content);
    int spamAmt;
    std::cout << "How many times do you want to spam (type -1 for infinite)? ";
    std::cin >> spamAmt;

    if (spamAmt == -1) {
        while (true) {
            CURL *curl;
            CURLcode res;

            curl_global_init(CURL_GLOBAL_DEFAULT);
            curl = curl_easy_init();

            if (curl) {
                curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, content.c_str());

                res = curl_easy_perform(curl);
                if(res != CURLE_OK) {
                    std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
                } else {
                    std::cout << "Webhook successfully nuked. (Posted)" << std::endl;
                }

                curl_easy_cleanup(curl);
            }

            curl_global_cleanup();
            startdcwf();
        }
    }
    for (int i = 0; i >= spamAmt; i++) {
            CURL *curl;
            CURLcode res;

            curl_global_init(CURL_GLOBAL_DEFAULT);
            curl = curl_easy_init();

            if (curl) {
                curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, content.c_str());

                res = curl_easy_perform(curl);
                if(res != CURLE_OK) {
                    std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
                } else {
                    std::cout << "Webhook successfully nuked. (Posted)" << std::endl;
                }

                curl_easy_cleanup(curl);
            }

            curl_global_cleanup();
            startdcwf();
    }
}


std::string to_lower(const std::string& str) {
    std::string lower_str = str;
    // Transform each character to lowercase
    std::transform(lower_str.begin(), lower_str.end(), lower_str.begin(), ::tolower);
    return lower_str;
}

std::string to_lower_each_word(const std::string& str) {
    std::string result;
    std::string word;

    // Loop through each character in the string
    for (char c : str) {
        // Check if the character is a space
        if (std::isspace(c)) {
            // If we have a word, convert it to lowercase and append it to the result
            if (!word.empty()) {
                result += to_lower(word) + " ";
                word.clear();
            }
        } else {
            // Add the character to the current word
            word += c;
        }
    }

    // Append the last word (if any) to the result
    if (!word.empty()) {
        result += to_lower(word);
    }

    return result;
}

int startdcwf() {
    std::string check = "HELLO WORLD";
    std::string lower_check = to_lower_each_word(check);
    if (lower_check == "hello world") {
        std::cout << "All checks passed, continuing" << std::endl;
    } else {
        std::cout << "Check failed, to_lower_each_word() failed" << std::endl;
        return 1;
    }
    std::string choice;
    std::string wh_url;
    if (wh_url == "") {
        std::cout << "Webhook URL: ";
        std::cin >> wh_url;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "╔══════════════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                                                                      ║" << std::endl;
    std::cout << "║  Webhook Spam | Bot mode | Webhook Deleter | Other | v1.0 DEV ALPHA  ║" << std::endl;
    std::cout << "║                                                                      ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════════════════════════╝" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "   >>> ";
    std::getline(std::cin, choice);

    std::string lower_choice = to_lower_each_word(choice);

    if (choice == "webhook spam") {
        webhook_spam(wh_url);
    } else if (choice == "bot mode") {
        std::cout << "v1.0 DEV ALPHA -- NOT IMPLEMENTED -- " << std::endl;
    } else if (choice == "webhook deleter") {
        send_whdel_req(wh_url);
    } else if (choice == "other") {
        std::cout << "╔═══════════════════════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║                                                                       ║" << std::endl;
        std::cout << "║  Webhook Deleter | Change WH name | URL Cracker | URL Finder | Other  ║" << std::endl;
        std::cout << "║                                                                       ║" << std::endl;
        std::cout << "╚═══════════════════════════════════════════════════════════════════════╝" << std::endl;
        std::cout << "" << std::endl;
        std::cout << "   >>> ";
        std::cin >> choice;
        if (choice == "webhook deleter") {
            std::cout << "v1.0 DEV ALPHA -- NOT IMPLEMENTED -- " << std::endl;
        } else if (choice == "change wh name") {
            std::cout << "v1.0 DEV ALPHA -- NOT IMPLEMENTED -- " << std::endl;
        } else if (choice == "url cracker") {
            std::cout << "v1.0 DEV ALPHA -- NOT IMPLEMENTED -- " << std::endl;
        } else if (choice == "url finder") {
            std::cout << "v1.0 DEV ALPHA -- NOT IMPLEMENTED -- " << std::endl;
        } else if (choice == "other") {
            std::cout << "v1.0 DEV ALPHA -- NOT IMPLEMENTED -- " << std::endl;
        }
    }

    return 0;
}

int main() {
    std::cout << "╔═════════════════════════════════════╗" << std::endl;
    std::cout << "║  ██████╗  ██████╗██╗    ██╗███████╗ ║" << std::endl;
    std::cout << "║  ██╔══██╗██╔════╝██║    ██║██╔════╝ ║" << std::endl;
    std::cout << "║  ██║  ██║██║     ██║ █╗ ██║█████╗   ║" << std::endl;
    std::cout << "║  ██║  ██║██║     ██║███╗██║██╔══╝   ║" << std::endl;
    std::cout << "║  ██████╔╝╚██████╗╚███╔███╔╝██       ║" << std::endl;
    std::cout << "║  ╚═════╝  ╚═════╝ ╚══╝╚══╝ ╚═╝      ║" << std::endl;
    std::cout << "╚═════════════════════════════════════╝" << std::endl;
    int res;
    wait(1, [&res](){
        res = send_request("https://www.google.com");
    });

    if (res != CURLE_OK) {
        std::cerr << "Please make sure that you have a stable WiFi/Ethernet connection." << std::endl;
        std::cout << "Retrying in 3 seconds..." << std::endl;
        wait(3, [&res](){
            main();
        });
    }
    else {
        std::cout << "Starting DiscordWebhookFucker!" << std::endl;
        startdcwf();
    }
    return 0;
}
