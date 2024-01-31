#include <iostream>
#include <thread>
#include <atomic>
#include <fstream>

using namespace std;
atomic<int> x, y, r1, r2, r3, r4;
int count_zz = 0, count_zo = 0, count_oz = 0, count_oo = 0;
int r[2][2][2][2];

void lb_litmus_test_relaxed(int iteration, memory_order mem_order)
{
    x.store(0);
    y.store(0);

    thread t1([&]
              {
        r1.store(x.load(mem_order), mem_order);
        y.store(1, mem_order); });

    thread t2([&]
              {
        r2.store(y.load(mem_order), mem_order);
        x.store(1, mem_order); });

    t1.join();
    t2.join();

    if (r1 == 1 && r2 == 1)
    {
        cout << "LB: Violation at iteration " << iteration << endl;
    }
}

void sb_litmus_test_relaxed(int iteration, memory_order mem_order)
{
    x.store(0);
    y.store(0);

    thread t1([&]
              {
        x.store(1, mem_order);
        r1.store(y.load(mem_order),mem_order); });

    thread t2([&]
              {
        y.store(1, mem_order);
        r2.store(x.load(mem_order), mem_order); });

    t1.join();
    t2.join();

    if (r1 == 0 && r2 == 0)
    {
        cout << "SB: Violation at iteration " << iteration << endl;
    }
}

void mp_litmus_test_relaxed(int iteration, memory_order mem_order)
{
    x.store(0);
    y.store(0);

    thread t1([&]
              {
        x.store(1, mem_order);
        y.store(1, mem_order); });

    thread t2([&]
              {
        r1.store(y.load(mem_order), mem_order);
        r2.store(x.load(mem_order), mem_order); });

    t1.join();
    t2.join();

    if (r1 == 1 && r2 == 0)
    {
        cout << "MP: Violation at iteration " << iteration << endl;
    }
}

void iriw_litmus_test_relaxed(int iteration, memory_order mem_order)
{
    x.store(0);
    y.store(0);

    thread t1([&]
              { x.store(1, mem_order); });

    thread t2([&]
              { y.store(1, mem_order); });

    thread t3([&]
              {
        r1.store(x.load(mem_order), mem_order);
        r2.store(y.load(mem_order), mem_order); });

    thread t4([&]
              {
        r3.store(y.load(mem_order), mem_order);
        r4.store(x.load(mem_order), mem_order); });

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    if (r1 == 1 && r2 == 0 && r3 == 1 && r4 == 0)
    {
        cout << "IRIW: Violation at iteration " << iteration << endl;
    }
}

int main()
{
    memory_order mem_order = memory_order_relaxed;

    for (int i = 0; i < 10000; ++i)
    {
        lb_litmus_test_relaxed(i, mem_order);

        if (r1 == 0 && r2 == 0)
            count_zz++;

        else if (r1 == 0 && r2 == 1)
            count_zo++;

        else if (r1 == 1 && r2 == 0)
            count_oz++;

        else
            count_oo++;
    }

    std::ofstream csv_file("Problem_3_Output.csv");
    csv_file << "Load Buffer Result, "
             << "Count" << endl;
    csv_file << "Count (r1:0 and r2:0):, " << count_zz << endl;
    csv_file << "Count (r1:1 and r2:0):, " << count_oz << endl;
    csv_file << "Count (r1:0 and r2:1):, " << count_zo << endl;
    csv_file << "Count (r1:1 and r2:1):, " << count_oo << endl;
    csv_file << "Num Valid test:, " << count_zo + count_oz + count_zz << endl;
    csv_file << "Num Invalid test:, " << count_oo << endl;
    csv_file << " " << endl;

    count_zz = 0, count_zo = 0, count_oz = 0, count_oo = 0;

    for (int i = 0; i < 10000; ++i)
    {
        sb_litmus_test_relaxed(i, mem_order);

        if (r1 == 0 && r2 == 0)
            count_zz++;

        else if (r1 == 0 && r2 == 1)
            count_zo++;

        else if (r1 == 1 && r2 == 0)
            count_oz++;

        else
            count_oo++;
    }

    csv_file << "Store Buffer Result, "
             << "Count" << endl;
    csv_file << "Count (r1:0 and r2:0):, " << count_zz << endl;
    csv_file << "Count (r1:1 and r2:0):, " << count_oz << endl;
    csv_file << "Count (r1:0 and r2:1):, " << count_zo << endl;
    csv_file << "Count (r1:1 and r2:1):, " << count_oo << endl;
    csv_file << "Num Valid test:, " << count_zo + count_oz + count_oo << endl;
    csv_file << "Num Invalid test:, " << count_zz << endl;
    csv_file << " " << endl;

    count_zz = 0, count_zo = 0, count_oz = 0, count_oo = 0;

    for (int i = 0; i < 10000; ++i)
    {
        mp_litmus_test_relaxed(i, mem_order);

        if (r1 == 0 && r2 == 0)
            count_zz++;

        else if (r1 == 0 && r2 == 1)
            count_zo++;

        else if (r1 == 1 && r2 == 0)
            count_oz++;

        else
            count_oo++;
    }

    csv_file << "Message Passing Result, "
             << "Count" << endl;
    csv_file << "Count (r1:0 and r2:0):, " << count_zz << endl;
    csv_file << "Count (r1:1 and r2:0):, " << count_oz << endl;
    csv_file << "Count (r1:0 and r2:1):, " << count_zo << endl;
    csv_file << "Count (r1:1 and r2:1):, " << count_oo << endl;
    csv_file << "Num Valid test:, " << count_zo + count_zz + count_oo << endl;
    csv_file << "Num Invalid test:, " << count_oz << endl;
    csv_file << " " << endl;

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                for (int l = 0; l < 2; l++)
                    r[i][j][k][l] = 0;
            }
        }
    }

    for (int i = 0; i < 10000; ++i)
    {
        iriw_litmus_test_relaxed(i, mem_order);

        r[r1][r2][r3][r4]++;
    }

    csv_file << "Independent Read Independent Write, "
             << "Count" << endl;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                for (int l = 0; l < 2; l++)
                {
                    csv_file << "Count (r1: " << i << " and r2: " << j << " and r3: " << k << " and r4: " << l << "):, " << r[i][j][k][l] << endl;
                }
            }
        }
    }

    csv_file << "Num Valid test:, " << 10000 - r[1][0][1][0] << endl;
    csv_file << "Num Invalid test:, " << r[1][0][1][0] << endl;
    csv_file.close();

    return 0;
}
