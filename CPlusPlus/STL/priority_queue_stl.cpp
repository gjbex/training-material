#include<functional>
#include <iostream>
#include<queue>
#include <vector>

class Job {
    public:
        Job(std::string const& n, int p)
            :job_name(n), job_priority{p} {
        };
        std::string& name() {
            return this->job_name;
        };
        int priority() {
            return this->job_priority;
        };
        bool operator<(Job job) {
            return this->priority() < job.priority();
        }
        void print() {
            std::cout << this->name() << ": "
                      << this->priority() << std::endl;
        }
    private:
        std::string job_name;
        int job_priority;
};

bool cmp(Job job1, Job job2) {
    return job1 < job2;
};

typedef std::function<bool(Job, Job)> job_cmp;
typedef std::priority_queue<Job, std::vector<Job>, job_cmp> job_queue;

int main(int argc, char *argv[]) {
    job_queue jobs(cmp);
    std::string names[] = {"gromacs", "amrvac", "beast", "beast", "fluent"};
    std::cout << "inserting in priory queue" << std::endl;
    for (auto name: names) {
        Job *job = new Job(std::string(name), std::rand() % 100);
        job->print();
        jobs.push(*job);
    }
    std::cout << "taking from priory queue" << std::endl;
    while (!jobs.empty()) {
        auto job = jobs.top();
        job.print();
        jobs.pop();
    }
    return 0;
}
