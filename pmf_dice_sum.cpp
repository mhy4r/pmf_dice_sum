#include <iostream>
#include <string>
#include <vector>
#include <map>

const char PRESENTATION_CHAR = '#';
const int UPPER_BOUND = 6;
const int LOWER_BOUND = 1;
const int NOT_A_INDEX = -1;

class Simulator 
{
    public:
        Simulator (int num_of_dices_) : num_of_dices_(num_of_dices_)
        {
            nums_ = std::vector<int> (num_of_dices_, 1);
            finished_ = false;
        }

        int generate()
        {
            int out = calculate();
            update();
            return out;
        }

        bool is_finished()
        {
            return finished_;
        }
    
    private:
        void update() 
        {
            auto copy = nums_;
            nums_[0]++;
            int idx;
            while ((idx = get_index_invalid()) != NOT_A_INDEX)
            {
                nums_[idx++] %= UPPER_BOUND;
                if (idx >= num_of_dices_)
                {
                    nums_ = copy;
                    finished_ = true;
                    return;
                }

                nums_[idx]++;
            }
        }

        int calculate()
        {
            int sum = 0;
            for (int i = 0; i  < num_of_dices_; ++i)
                sum += nums_[i];
            return sum;
        }

        int get_index_invalid() 
        {
            for (int i = 0; i  < num_of_dices_; ++i)
                if (nums_[i] > 6)
                    return i;
            return NOT_A_INDEX;
        }

        std::vector<int> nums_;
        int num_of_dices_;
        bool finished_;
};

std::string generate_bar_string(int length)
{
    std::string out;
    for (int i = 0; i < length; ++i)
        out += PRESENTATION_CHAR;
    return out;
}

void show(std::map<int, int>& result)
{
    for (auto [key, value] : result)
    {
        printf("%3d ", key);
        std::cout << generate_bar_string(value) << std::endl;
    }
}

int main()
{
    std::map<int, int> result;
    int num_of_dices;
    std::cout << "Enter number of dices: ";
    std::cin >> num_of_dices;
    Simulator dice_throw(num_of_dices);
    while (!dice_throw.is_finished()) {
        int trial = dice_throw.generate();
        ++result[trial];
    }
    show(result);
    return 0;
}