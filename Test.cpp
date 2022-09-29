#include <iostream>

int get_distance(int first_x, int first_y, int second_x, int second_y)
{
    int dist_x = abs(first_x - second_x);
    int dist_y = abs(first_y - second_y);

    if(dist_x > dist_y)
    {
        return (14 * dist_y) + (10 * (dist_x - dist_y));
    }

    return (14 * dist_x) + (10 * (dist_y - dist_x));
}


int main()
{
    std::cout << get_distance(0, 0, 0, 10);

    return 0;
}
