#include <iostream>
#include <map>
#include <set>

using namespace std;

int main()
{
  int no_of_transactions{};
  cin>>no_of_transactions;

  map<string, int> nameAmt;

  string person1,person2;
  int amount;

  while(no_of_transactions)
  {
    cin>>person1>>person2>>amount;

    if(nameAmt.count(person1) == 0)
      nameAmt[person1] = -amount;
    else
      nameAmt[person1] -= amount;

    if(nameAmt.count(person2) == 0)
      nameAmt[person2] = amount;
    else
      nameAmt[person2] += amount;

    no_of_transactions--;
  }

  // Making the multiset

  multiset<pair<int, string>> settle;

  for(auto person : nameAmt)
  {
    string name = person.first;

    int due = person.second;

    if(due != 0)
    {
      settle.insert(make_pair(due, name));
    }
  }

  // Settlement

  int count = 0;

    while(!settle.empty())
    {
      auto low = settle.begin();

      auto high = prev(settle.end());

      int debit = low->first;
      string debit_name = low->second;

      int credit = high->first;
      string credit_name = high->second;

      // Removing from multiset as now their values will be changed.

      settle.erase(low);

      settle.erase(high);

      int settled_amount = min(-debit, credit);

      debit = debit + settled_amount;

      credit = credit - settled_amount;

      cout<<"\n"<<debit_name<<" pays "<<settled_amount<<" to "<<credit_name;
      count++;

      if(debit != 0)
        settle.insert(make_pair(debit, debit_name));

      if(credit != 0)
        settle.insert(make_pair(credit, credit_name));
    }

    cout<<"\n\nNumber of trasctions reduced to : "<<count<<endl;

  return 0;
}
