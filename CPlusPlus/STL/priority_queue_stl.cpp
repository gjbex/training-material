#include<functional>
#include <iostream>
#include<queue>
#include <vector>

class Job {
    private:
        std::string _name;
        int _priority;
    public:
        Job(std::string const& name, const int priority) :
            _name {name}, _priority {priority} {};
        std::string name() const { return _name; };
        int priority() const { return _priority; };
        friend bool operator<(const Job& job1, const Job& job2) {
            return job1.priority() < job2.priority();
        };
        friend std::ostream& operator<<(std::ostream& out, const Job& job);
};

std::ostream& operator<<(std::ostream& out, const Job& job) {
    return out << job.name() << ": " << job.priority();
}

bool cmp(const Job& job1, const Job& job2) {
    return job1 < job2;
};

using job_cmp = std::function<bool(const Job&, const Job&)>;
using job_queue = std::priority_queue<Job,std::vector<Job>,job_cmp>;

int main() {
    job_queue jobs(cmp);
    std::string names[] = {"gromacs", "amrvac", "beast", "beast", "fluent"};
    std::cout << "inserting in priory queue" << std::endl;
    for (const auto& name: names) {
        Job job(std::string(name), std::rand() % 100);
        std::cout << job << std::endl;
        jobs.push(job);
    }
    std::cout << "taking from priory queue" << std::endl;
    while (!jobs.empty()) {
        auto job = jobs.top();
        std::cout << job << std::endl;
        jobs.pop();
    }
    return 0;
}
