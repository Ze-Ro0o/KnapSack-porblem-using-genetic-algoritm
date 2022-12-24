#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>
#include <utility>
#include <iostream>

using namespace std;
typedef long long unsigned int ll;
ll numtest;
ll calfitness(vector<ll> chromosome, vector<pair<ll, ll> > vec)
{
    ll counter = 0;
    for (size_t i = 0; i < chromosome.size(); i++)
    {
        counter += (chromosome[i]) * (vec[i].second);
    }
    return counter;
}
ll calweight(vector<ll> chromosome, vector<pair<ll, ll> > vec)
{
    ll counter = 0;
    for (size_t i = 0; i < chromosome.size(); i++)
    {
        counter += (chromosome[i]) * (vec[i].first);
    }
    return counter;
}
bool valid(vector<ll> chromosome, vector<pair<ll, ll> > vec, ll size)
{
    if (calweight(chromosome, vec) <= size)
        return true;
    else
        return false;
}
ll calNumElements(vector<ll> chromosome)
{
    ll counter = 0;
    for (size_t i = 0; i < chromosome.size(); i++)
    {
        if(chromosome[i]==1)
        {
            counter++;
        }
    }
    return counter;
}
pair<ll, vector<ll> > a7sanwa7d(vector<pair<ll, vector<ll> > > x)
{
    sort(x.begin(), x.end());
    return x[x.size()-1];
}

const int populationSize = 1000;
ll knapSackSize, numItems, x, y, counter = 0;
ll random, numGenerations = 200;
pair<ll, vector<ll> > firstchild1,secondchild2;
vector<pair<ll, vector<ll>>> candidates;
vector<ll> chromosomesFitness, chromosomesCumulativeFitness;
vector<ll> firstparent, secondparent, firstchild, secondchild;
vector<std::pair<ll, ll> > vec;
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    cin >> numtest;
    for (int z = 0; z < numtest; ++z)
    {
        counter=0;
        vector<pair<ll, vector<ll> >> chromosome(populationSize);
        firstparent.clear();secondparent.clear();firstchild.clear();secondchild.clear();candidates.clear();
        chromosomesFitness.clear();chromosomesCumulativeFitness.clear();vec.clear();
        pair<ll, ll> pair;
        cin >> knapSackSize;
        cin >> numItems;
        for (int i = 0; i < numItems; ++i)
        {
            cin >> x >> y;
            pair = make_pair(x, y);
            vec.push_back(pair);
        }
        for (int k = 0; k < populationSize; k++)
        {
            ll weight = 0;
            //initialization loop
            for (int j = 0; j < numItems; j++)
            {
                random = rand() % 2; // random  0 or 1
                if (random == 1 && weight <= knapSackSize)// handling ks size problem
                {
                    chromosome[k].second.push_back(random);
                    weight += vec[j].first;
                }
                else
                {
                    chromosome[k].second.push_back(0);
                }
                if(weight>knapSackSize)
                {
                    chromosome[k].second.pop_back();//remove last 1
                    chromosome[k].second.push_back(0);//replace it by 0
                }
            }
        }
        // applying fitness function
        for (int j = 0; j < populationSize; j++)
        {
            counter = 0;
            for (int k = 0; k < numItems; k++)
            {
                counter += (chromosome[j].second[k]) * (vec[k].second); // fitness(value)
            }
            chromosome[j].first = counter;
            chromosomesFitness.push_back(counter);//not important(just to get size)
        }


        // loop for generations
        for(int g = 0; g < numGenerations; g++)
        {
            firstparent.clear();secondparent.clear();
            // calculating cumulative fitness
            chromosomesCumulativeFitness = chromosomesFitness;//only to fill the list
            chromosomesCumulativeFitness[0] = chromosome[0].first;//first cumulative fitness = first fitness
            for (int k = 1; k < populationSize; k++)
            {
                chromosomesCumulativeFitness[k] = chromosome[k].first + chromosomesCumulativeFitness[k - 1];
            }
            // choosing first parent
            int r1 = rand() % (chromosomesCumulativeFitness[populationSize - 1] - 0 + 1) + 0;

            if (r1 >= 0 && r1 < chromosomesCumulativeFitness[0])
            {
                firstparent = chromosome[0].second;
            }
            for (int k = 1; k < chromosomesCumulativeFitness.size(); k++)
            {
                if (r1 >= chromosomesCumulativeFitness[k - 1] && r1 < chromosomesCumulativeFitness[k])
                {
                    firstparent = chromosome[k].second;
                    break;
                }
            }
            // choosing second parent
            int r2 = rand() % (chromosomesCumulativeFitness[populationSize - 1] - 0 + 1) + 0;
            if (r2 >= 0 && r2 < chromosomesCumulativeFitness[0])
            {
                secondparent = chromosome[0].second;
            }
            for (int k = 1; k < chromosomesCumulativeFitness.size(); k++)
            {
                if (r2 >= chromosomesCumulativeFitness[k - 1] && r2 < chromosomesCumulativeFitness[k])
                {
                    secondparent = chromosome[k].second;
                    break;
                }
            }
            int xc = rand() % ((chromosomesCumulativeFitness.size() - 1) - 1 + 1) + 1;
            int rc = rand() % (numItems-2 + 1) + 1; // random between 0 and 1
            int pc = 0.7;//constant
            int pm = 0.1;//constant

            if (rc <= pc) // crossover
            {
                for (int i = 0; i < xc; i++)
                {
                    firstchild[i] = firstparent[i];
                    secondchild[i] = secondparent[i];
                }
                for (int i = xc; i < firstparent.size(); i++)
                {
                    firstchild[i] = secondparent[i];
                    secondchild[i] = firstparent[i];
                }
            }
            else // no crossover
            {
                firstchild = firstparent;
                secondchild = secondparent;
            }
            // mutation
            for (int i = 0; i < firstparent.size(); i++)
            {
                int randNum = rand() % (1 - 0 + 1) + 0;
                if (firstchild[i] == 0 && randNum <= pm)
                {
                    firstchild[i] = 1;
                }
                else if (firstchild[i] == 1 && randNum <= pm)
                {
                    firstchild[i] = 0;
                }
            }
            for (int i = 0; i < secondparent.size(); i++)
            {
                int randNum = rand() % (1 - 0 + 1) + 0;
                if (secondchild[i] == 0 && randNum <= pm)
                {
                    secondchild[i] = 1;
                }
                else if (secondchild[i] == 1 && randNum <= pm)
                {
                    secondchild[i] = 0;
                }
            }
            std::sort(chromosome.begin(), chromosome.end());
            ll ff = calfitness(firstchild, vec);  // first child fitness
            ll sf = calfitness(secondchild, vec); // second child fitness
            firstchild1.first = ff;
            secondchild2.first = sf;
            firstchild1.second = firstchild;
            secondchild2.second = secondchild;

            candidates.push_back(firstchild1);
            candidates.push_back(secondchild2);
            candidates.push_back(chromosome[0]);
            candidates.push_back(chromosome[1]);
            sort(candidates.begin(),candidates.end());
            if(valid(candidates[2].second,vec,knapSackSize)){
                chromosome[0]=candidates[2];
            }
            if(valid(candidates[3].second,vec,knapSackSize)){
                chromosome[1]=candidates[3];
            }
        }
        std::sort(chromosome.begin(), chromosome.end());
        vector <ll> bestOne= chromosome[populationSize-1].second;
        ll finalFitness =calfitness(bestOne,vec);
        ll finalWeight = calweight(bestOne,vec);
        ll finalNumElements = calNumElements(bestOne);
        cout<<""<<endl;
        cout<<"------------------------------------------"<<"TestCase "<<z+1<<endl;
        cout<<"Number of selected items: "<<finalNumElements<<endl;
        cout<<"Total Weight: "<<finalWeight<<endl;
        cout<<"Total Value: "<<finalFitness<<endl;
        cout<<"Items Selected: "<<endl;
        for(int i=0; i<bestOne.size(); i++)
        {
            if(bestOne[i]==1)
            {
                cout<<"["<<"Value="<<vec[i].second<<", "<<"Weight="<<vec[i].first<<"]"<<endl;
            }
        }
        cout<<"------------------------------------------------------"<<endl;
    }
    return 0;
}
