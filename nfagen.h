#include <iostream>
using namespace std;
int nodes_assigned=0;

class node
{
public:
	int state_number,displayed_status,assigned_status; 
	node* up;
	char up_value;
	node* down;
	char down_value;
	node()
	{
		state_number=0;
		displayed_status=0;
		up_value='#';
		down_value='#';
		up=NULL;
		down=NULL;
	}
};

class nfa
{
public:
	node* start;
	node* end;
	nfa()
	{
		start=new node();
		end=new node();
	}
};


nfa single_nfa(char value)
{
	nfa x;
	
	x.start->up=x.end;
	x.start->up_value=value;
	
	return x;
}

nfa and_nfa(nfa first,nfa second)
{
	nfa x;
	
	x.start=first.start;
	first.end=second.start;
	first.start->up=second.start;
	x.end=second.end;
	
	return x;
}


nfa or_nfa(nfa first,nfa second)
{
	nfa x;
	
	x.start->up=first.start;
	x.start->up_value='^';
	
	x.start->down=second.start;
	x.start->down_value='^';
	
	first.end->up=x.end;
	first.end->up_value='^';
	
	second.end->up=x.end;
	second.end->up_value='^';
	
	return x;
}
nfa star_nfa(nfa first)
{
	nfa x;
	
	x.start->up=first.start;
	x.start->up_value='^';

	x.start->down=x.end;
	x.start->down_value='^';
	
	first.end->up=x.end;
	first.end->up_value='^';
	
	first.end->down=first.start;
	first.end->down_value='^';
	
	return x;
}
void assign_states(node* start)
{
	if(start->assigned_status==0)
	{
		nodes_assigned++;
		start->state_number=nodes_assigned;
		start->assigned_status=1;
		if(start->up_value!='#')
			assign_states(start->up);
		if(start->down_value!='#')
			assign_states(start->down);
	}
}
void display_nfa_helper(node* start)
{
	if(start->displayed_status==0)
	{
		cout<<start->state_number;
		if(start->up_value=='#')
			cout<<"\t-1";
		else
			cout<<"\t"<<start->up->state_number;
		cout<<"\t"<<start->up_value;
		
		if(start->down_value=='#')
			cout<<"\t-1";
		else
			cout<<"\t     "<<start->down->state_number;
		cout<<"\t     "<<start->down_value<<" \n";
		start->displayed_status=1;
		if(start->up_value!='#')
			display_nfa_helper(start->up);
		if(start->down_value!='#')
			display_nfa_helper(start->down);
	}
}

void display_nfa(nfa x)
{
	assign_states(x.start);
	cout<<"\n'#' represents link not assigned.\n\n";
	cout<<"State left_link left_val right_link right_val\n";
	display_nfa_helper(x.start);
	nodes_assigned=0;
}

/*
For example and testing

int main()
{
	nfa y=star_nfa(single_nfa('a'));
	display_nfa(y);
	nfa x=and_nfa(or_nfa(single_nfa('a'),single_nfa('b')),star_nfa(single_nfa('c')));
	display_nfa(x);
}
//*/
