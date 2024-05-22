
//Horváth Áron, X2ZA3U
//Kempner-sor kiszámolása

    #include <iostream>
    #include <string>
    #include <fstream>
    #include <vector>
    #include <algorithm>
    #include <math.h>

    using namespace std;
    
    const int MAXK = 50;
    const int MAXI = 5000;
    const int KEZD = 4; //kezdetben hány oszlop legyen kitöltve

    double arr[MAXK][MAXI];
    
    bool jo(int n)
    {
        string s = to_string(n);
        int l = s.length() - 1;
        while (l >= 0)
        {
            if (s[l] == '9')
            {
                return false;
            }
            l--;
        }
        return true;
    }

    void kezd_tolt(int i) // i. oszlop kitöltése a klasszikus technikával 
    {
        for (size_t j = pow(10,i-1); j < pow(10,i); j++)
        {
            if (jo(j))
            {
                for (size_t k = 1; k <= MAXK; k++)
                {
                    arr[k-1][i-1] += 1/pow(j, k);
                }
            }
        }
    }
    
    int nCk(int n, int k)
    {   
        if (k>n-k)
        {
            return nCk(n, n - k);
        }
        double p = 1;
        for (size_t i = 1; i <= k; i++)
        {
            p *= (double)(n-k+i) / i;
        }
        return p;
    }
    
    int c_kl(int k, int l)
    {
        return (pow(-1, l) * nCk(k + l - 1, l));
    }
    
    void kitolt(int k, int i)
    {
        double s = 0;
        for (size_t d = 0; d <= 8; d++)
        {
            for (size_t l = 0; l <= MAXK -k; l++)
            {
                s += c_kl(k, l) * pow(d, l) / pow(10, k + l) * arr[k+l-1][i-2];
            }
        }
        arr[k-1][i-1]=s;
    }
    
    int main()
    {
        for (size_t i = 1; i <= KEZD; i++)
        {
            kezd_tolt(i);
        }
        for (size_t i = KEZD+1; i <= MAXI; i++)
        {
            for (size_t k = 1; k <= MAXK; k++)
            {
                kitolt(k,i);
            }
        }

        //elsõ sor összegzése
        double sum = 0;
        for (size_t i = 0; i < MAXI; i++)
        {
            sum += arr[0][i];
        }
        cout.precision(20);
        cout << sum << endl;
        cin.get();
    }