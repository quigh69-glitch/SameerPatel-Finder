#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <windows.h>

namespace fs = std::filesystem;

int get_levenshtein_distance(const std::string& s1, const std::string& s2) {
    int n = (int)s1.length();
    int m = (int)s2.length();
    if (n == 0) return m;
    if (m == 0) return n;
    std::vector<std::vector<int>> d(n + 1, std::vector<int>(m + 1));
    for (int i = 0; i <= n; i++) d[i][0] = i;
    for (int j = 0; j <= m; j++) d[0][j] = j;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char c1 = (char)tolower(s1[i - 1]);
            char c2 = (char)tolower(s2[j - 1]);
            if (c1 == '_') c1 = ' ';
            if (c2 == '_') c2 = ' ';
            int cost = (c1 == c2) ? 0 : 1;
            d[i][j] = (std::min)({ d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + cost });
        }
    }
    return d[n][m];
}

int main() {
    std::string target = "Sameer Patel"; //target
    std::string root = "C:\\"; //root
    std::vector<std::string> found_paths;

    std::cout << "--- SimpleFinder ---" << std::endl;
    std::cout << "Scan C:\\ ..." << std::endl;

    std::error_code ec;
    auto it = fs::recursive_directory_iterator(root, fs::directory_options::skip_permission_denied, ec);

    for (auto entry_it = fs::begin(it); entry_it != fs::end(it); ) {
        try {
            const auto& entry = *entry_it;
            std::string name = entry.path().filename().string();

            if (!name.empty()) {
                int dist = get_levenshtein_distance(name, target);

                if (dist <= 5) {
                    std::string low_name = name;
                    for (auto& c : low_name) c = (char)tolower(c);

                    if (low_name.find('s') != std::string::npos && low_name.find('p') != std::string::npos) {
                        found_paths.push_back(entry.path().string());
                        std::cout << "[" << found_paths.size() << "] Found: " << name << std::endl;
                    }
                }
            }
        }
        catch (...) {}

        entry_it.increment(ec);
        if (ec) {
            ec.clear();
            continue;
        }
    }

    std::cout << "\n--- Scan Finished. Found: " << found_paths.size() << " ---" << std::endl;

  if (!found_paths.empty()) {
        std::cout << "  _____  _____  " << std::endl;
        std::cout << " / ____||  __ \\ " << std::endl;
        std::cout << "| (___  | |__) |" << std::endl;
        std::cout << " \\___ \\ |  ___/ " << std::endl;
        std::cout << " ____) || |     " << std::endl;
        std::cout << "|_____/ |_|     " << std::endl;
    }
    else {
        std::cout << "Not found. System is clean." << std::endl;
        system("pause");
        return 0;
    }

    while (true) {
        std::cout << "\nEnter number to open (or '0' to exit): ";
        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        if (choice == 0) break;
        if (choice > 0 && choice <= (int)found_paths.size()) {
            std::string cmd = "explorer /select,\"" + found_paths[choice - 1] + "\"";
            system(cmd.c_str());
            std::cout << "Opened match #" << choice << std::endl;
        }
        else {
            std::cout << "Invalid number!" << std::endl;
        }
    }

    return 0;
}
