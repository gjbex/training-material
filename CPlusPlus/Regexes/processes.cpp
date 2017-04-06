#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <time.h>

using namespace std;

time_t compute_duration(const string& start_str, const string& end_str) {
    struct tm start_tm, end_tm;
    memset(&start_tm, 0, sizeof(struct tm));
    memset(&end_tm, 0, sizeof(struct tm));
    if (!strptime(start_str.c_str(), "%Y-%m-%d %H:%M:%S", &start_tm)) {
        cerr << "# warning: string '" << start_str << "' is invalid"
             << endl;
        return 0;
    }
    if (!strptime(end_str.c_str(), "%Y-%m-%d %H:%M:%S", &end_tm)) {
        cerr << "# warning: string '" << start_str << "' is invalid"
             << endl;
        return 0;
    }
    time_t start_time = mktime(&start_tm);
    time_t end_time = mktime(&end_tm);
    return end_time - start_time;
}

int main() {
    string line;
    map<string, string> event_starts;
    map<string, time_t> event_durations;
    const string time_pat {R"((\d{4}-\d{2}-\d{2}\s+\d{2}:\d{2}:\d{2}))"};
    const string type_pat {R"(\[(\w+)\])"};
    const string event_pat {R"((begin|end)\s+(.+)\s*$)"};
    const string sep_pat {R"(\s+)"};
    regex pat(time_pat + ":" + sep_pat + type_pat + sep_pat + event_pat);
    while (getline(cin, line)) {
        smatch matches;
        if (regex_search(line, matches, pat)) {
            const string event_id = matches[4];
            if (matches[3] == "begin") {
                event_starts[event_id] = matches[1];
            } else if (matches[3] == "end") {
                if (event_starts.find(event_id) != event_starts.end()) {
                    auto duration = compute_duration(event_starts[event_id],
                                                     matches[1]);
                    event_durations[event_id] = duration;
                } else {
                    cerr << "# warning: end event for '" << event_id
                         << "' without start event" << endl;
                }
            }
        }
    }
    for (auto event: event_durations)
        cout << event.first << ": " << event.second << endl;
    return 0;
}
