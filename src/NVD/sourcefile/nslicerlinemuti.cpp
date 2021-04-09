#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <set>
#include <stack>

using namespace std;

set<string> function_of_resource;

void  ReadDataFromLlvmfile(string llvmfilename,string holelinenum,vector<string> &llvmNX,string &funcname)
{
	vector<string> v;
	vector<string> result;
	ifstream fin(llvmfilename.c_str());
	string  s;
	string  temp;
	while (getline(fin, s))
	{
		v.push_back(s);
	}

	vector<char> line; //line
	for (int j = 0; j < holelinenum.size(); ++j)
	{
		line.push_back(holelinenum[j]);
	}

	int linesize = line.size();
	string functionname;
	switch (linesize)
	{
		case 2:
		{
			for (int i = 0; i < v.size(); i++)
			{
				for (int j = 0; j < v[i].size(); ++j)
				{
					if (v[i][j - 16] == 'D'&&v[i][j - 3] == 'n'&&v[i][j - 2] == 'e'&&v[i][j - 1] == ':'&&v[i][j] == ' '&&v[i][j + 1] == line[0] && v[i][j + 2] == line[1] && v[i][j + 3] == ',')
					{
						for(int k = i-1;k >= 0;--k){
							// 防止找到头文件中的函数
							if(v[k].find("distinct !DISubprogram")!= string::npos){ 
								if(v[k+1].find("!DIFile") == string::npos){
									string::size_type pos = v[k].find('"'),last = v[k].find('"',pos+1);		
									functionname = v[k].substr(pos+1,last-pos-1);
									if(function_of_resource.find(functionname) != function_of_resource.end()){
										for (int p = 0; v[i][p] != ' '; ++p)
										{
											temp += v[i][p];
										}
										result.push_back(temp);
										temp = "";
									}
								}
								break;
							}
						}
					}
				}
			}
			if(!result.empty()){
				for (int i = 0; i < v.size(); ++i)
				{
					if(v[i].find(result[0])!=string::npos)
					{
						for (int j = i; j >=0; j--)
						{
							if(v[j].find("define")!=string::npos)
							{
								funcname=v[j].substr(0,v[j].find('('));
								break;
							}
						}
						break;
					}
				}
			}
			else
				funcname="";
			for (int i = 0; i < v.size(); ++i)
			{
				for (int i1 = 0; i1 < result.size(); ++i1)
				{
					int stringend2 = result[i1].size();
					int stringend1 = v[i].size();
					for (int i2 = stringend2 - 1; i2 >= 0;)
					{
						if (v[i][stringend1 - 1] == result[i1][i2]) {
							i2--; stringend1--;
							if (i2 == 0&&v[i][stringend1-1]=='!') {
								temp = v[i];
								if(temp.substr(2,36)!="call void @llvm.dbg.declare(metadata")
									llvmNX.push_back(temp);
								temp = "";
							}
						}
						else 
							break;
					}
				}
			}
			break;
		}
		case 1:
		{
			for (int i = 0 ; i < v.size(); i++)
			{
				for (int j = 0; j < v[i].size(); ++j)
				{
					if (v[i][j - 16] == 'D'&&v[i][j - 3] == 'n'&&v[i][j - 2] == 'e'&&v[i][j - 1] == ':'&&v[i][j] == ' '&&v[i][j + 1] == line[0] && v[i][j + 2] == ',')
					{
						for(int k = i-1;k >= 0;--k){
							if(v[k].find("distinct !DISubprogram")!= string::npos){ 
								if(v[k+1].find("!DIFile") == string::npos){
									string::size_type pos = v[k].find('"'),last = v[k].find('"',pos+1);		
									functionname = v[k].substr(pos+1,last-pos-1);
									if(function_of_resource.find(functionname) != function_of_resource.end()){
										for (int p = 0; v[i][p] != ' '; ++p)
										{
											temp += v[i][p];
										}
										result.push_back(temp);
										temp = "";
									}
								}
								break;
							}
						}
					}
				}
			}
			if(!result.empty()){
				for (int i = 0; i < v.size(); ++i)
				{
					if(v[i].find(result[0])!=string::npos)
					{
						for (int j = i; j >=0; j--)
						{
							if(v[j].find("define")!=string::npos)
							{
								funcname=v[j].substr(0,v[j].find('('));
								break;
							}
						}
						break;
					}
				}
			}
			else
				funcname="";
			for (int i = 0; i < v.size(); ++i)
			{
				for (int i1 = 0; i1 < result.size(); ++i1)
				{
					int stringend2 = result[i1].size();
					int stringend1 = v[i].size();
					for (int i2 = stringend2 - 1; i2 >= 0;)
					{
						if (v[i][stringend1 - 1] == result[i1][i2]) {
							i2--; stringend1--;
							if (i2 == 0&&v[i][stringend1-1]=='!') {
								temp = v[i];
								if(temp.substr(2,36)!="call void @llvm.dbg.declare(metadata")
									llvmNX.push_back(temp);
								temp = "";
							}
						}
						else 
							break;
					}
				}
			}
			break;
		}
		case 3:
		{
			for (int i = 0 ; i < v.size(); i++)
			{
				for (int j = 0; j < v[i].size(); ++j)
				{
					if (v[i][j - 16] == 'D'&&v[i][j - 3] == 'n'&&v[i][j - 2] == 'e'&&v[i][j - 1] == ':'&&v[i][j] == ' '&&v[i][j + 1] == line[0] && v[i][j + 2] == line[1] && v[i][j + 3] == line[2] && v[i][j + 4] == ',')
					{
						for(int k = i-1;k >= 0;--k){
							if(v[k].find("distinct !DISubprogram")!= string::npos){ 
								if(v[k+1].find("!DIFile") == string::npos){
									string::size_type pos = v[k].find('"'),last = v[k].find('"',pos+1);		
									functionname = v[k].substr(pos+1,last-pos-1);
									if(function_of_resource.find(functionname) != function_of_resource.end()){
										for (int p = 0; v[i][p] != ' '; ++p)
										{
											temp += v[i][p];
										}
										result.push_back(temp);
										temp = "";
									}
								}
								break;
							}
						}
					}
				}
			}		
			if(!result.empty()){
				for (int i = 0; i < v.size(); ++i)
				{
					if(v[i].find(result[0])!=string::npos)
					{
						for (int j = i; j >=0; j--)
						{
							if(v[j].find("define")!=string::npos)
							{
								funcname=v[j].substr(0,v[j].find('('));
								break;
							}
						}
						break;
					}
				}
			}
			else 
				funcname="";
			for (int i = 0; i < v.size(); ++i) 
			{
				for (int i1 = 0; i1 < result.size(); ++i1)
				{
					int stringend2 = result[i1].size();
					int stringend1 = v[i].size();
					for (int i2 = stringend2 - 1; i2 >= 0;)
					{
						if (v[i][stringend1 - 1] == result[i1][i2]) {
							i2--; stringend1--;
							if (i2 == 0&&v[i][stringend1-1]=='!') {
								temp = v[i];
								if(temp.substr(2,36)!="call void @llvm.dbg.declare(metadata")
									llvmNX.push_back(temp);
								temp = "";
							}
						}
						else 
							break;
					}
				}
			}
			break;
		}
		case 4:
		{
			for (int i = 0; i < v.size(); i++)
			{
				for (int j = 0; j < v[i].size(); ++j)
				{
					if (v[i][j - 16] == 'D'&&v[i][j - 3] == 'n'&&v[i][j - 2] == 'e'&&v[i][j - 1] == ':'&&v[i][j] == ' '&&v[i][j + 1] == line[0] && v[i][j + 2] == line[1] && v[i][j + 3] == line[2] && v[i][j + 4] == line[3] && v[i][j + 5] == ',')
					{
						for(int k = i-1;k >= 0;--k){
							if(v[k].find("distinct !DISubprogram")!= string::npos){ 
								if(v[k+1].find("!DIFile") == string::npos){
									string::size_type pos = v[k].find('"'),last = v[k].find('"',pos+1);		
									functionname = v[k].substr(pos+1,last-pos-1);
									if(function_of_resource.find(functionname) != function_of_resource.end()){
										for (int p = 0; v[i][p] != ' '; ++p)
										{
											temp += v[i][p];
										}
										result.push_back(temp);
										temp = "";
									}
								}
								break;
							}
						}
					}
				}
			}
			if(!result.empty()){
				for (int i = 0; i < v.size(); ++i)
				{
					if(v[i].find(result[0])!=string::npos)
					{
						for (int j = i; j >=0; j--)
						{
							if(v[j].find("define")!=string::npos)
							{
								funcname=v[j].substr(0,v[j].find('('));
								break;
							}
						}
						break;
					}
				}
			}
			else 
				funcname="";
			for (int i = 0; i < v.size(); ++i)     
			{
				for (int i1 = 0; i1 < result.size(); ++i1)
				{
					int stringend2 = result[i1].size();
					int stringend1 = v[i].size();
					for (int i2 = stringend2 - 1; i2 >= 0;)
					{
						if (v[i][stringend1 - 1] == result[i1][i2]) {
							i2--; stringend1--;
							if (i2 == 0&&v[i][stringend1-1]=='!') {
								temp = v[i];
								if(temp.substr(2,36)!="call void @llvm.dbg.declare(metadata")
									llvmNX.push_back(temp);
								temp = "";
							}
						}
						else 
							break;
					}
				}
			}
			break;
		}
	}
}

struct point
{	
	string funcname;
	string line;
	vector<string> var;
};

struct useloc
{
	string funcname;
	string line;
	string var;
};

int main(int argc, char *argv[])
{
	char cmd[2000];

	set<string> holefunct; //漏洞函数
	
	vector<string> v;
	string s,temp;
	
	vector<string> llvmNX;
	vector<vector<string> > vllvmNX;

	string llvm;
	vector<string> vllvm;

	string funcname;
	vector<string> vfuncname;


	vector<int> vline; 	//保存源码中的漏洞行号
	int linetemp;

	string txt;
	ifstream holeline(argv[1]); //argv[1] 是 tmp.txt
	while(holeline >> txt){
		holeline >> linetemp;
		vline.push_back(linetemp);
	}
	// 如果漏洞行号为0 则退出
	if(linetemp == 0) return 0;

	string txt1,back;

    	int name=txt.size();
    	int name1=txt.size();
	
	ifstream recource(txt.c_str());
	string fline;
	string::size_type pos;
	// 保存源码中的函数
	while(getline(recource,fline)){
		if((pos = fline.find('('))!= string::npos && fline.find(';') == string::npos){
			fline = fline.substr(0,pos);
			stringstream sfline(fline);
			while(sfline >> fline){}
			if(fline.length() > 1 && fline[0] == '*'){
				fline = fline.substr(1);
			}
			function_of_resource.insert(fline);
		}
	}

	ifstream hole("holefunct.txt");
	string ver,version,funct,cname,fname,cveid,cve;	
	while(txt[name1-1]!='.')
    	{
      		name1--;
	}
	string filename=txt.substr(txt.find_last_of('/')+1,txt.find_last_of('.')-txt.find_last_of('/')-1);
    	txt1=(txt.substr(0,txt.find_last_of('/')));
	txt1=(txt1.substr(0,txt1.find_last_of('/')));
	ver = (txt1.substr(txt1.find_last_of('/')+1));
	txt1=(txt1.substr(0,txt1.find_last_of('/')));
	cve = (txt1.substr(txt1.find_last_of('/')+1));
	
	// holefunct保存漏洞函数
	while(getline(hole,funct)){
		stringstream ss(funct);
		ss >>cveid >> version >> fname >> funct;
		cname = txt.substr(txt.find_last_of('/')+1);
		if(cve == cveid && version == ver && fname == cname)
			holefunct.insert(funct); 
	}   

	string llvmfilename;

  	while(txt[name1-1]!='/')
        {
    		name1--;
    	}

	ifstream in(argv[2]); //argv[2] 是 dataxxx.txt
	string line,word;
	vector<point> vvp;
	bool flag;
	// vvp中保存漏洞函数中的关注点 
	while (getline(in, line))
	{
		vector<string> funcorline;
		istringstream record(line);
		while(record>>word)
			funcorline.push_back(word);
		if(funcorline.size() == 1  && !(funcorline[0][0] <= '9' && funcorline[0][0] >= '0')){
			funct = funcorline[0];
			if(holefunct.find(funct) != holefunct.end()){
				flag = true;			
			}
			else{
				flag = false;
			}
 		}
		if(flag){
			if(funcorline.size() > 1){
				point varandline;
				varandline.funcname = funct;
				varandline.line = funcorline[0];
				for(int i = 1;i < funcorline.size();++i){
					varandline.var.push_back(funcorline[i]);
				}
				vvp.push_back(varandline);
			}
		}
	}

	ifstream data_val(argv[3]); //argv[3] 是 data-val.txt
	vector<useloc> lastuseval;
	// vvp中保存漏洞函数中的关注点 
	while (getline(data_val, line))
	{
		vector<string> funcorline;
		istringstream record(line);
		while(record>>word)
			funcorline.push_back(word);
		if(funcorline.size() == 1  && !(funcorline[0][0] <= '9' && funcorline[0][0] >= '0')){
			funct = funcorline[0];
			if(holefunct.find(funct) != holefunct.end()){
				flag = true;			
			}
			else{
				flag = false;
			}
 		}
		if(flag){
			if(funcorline.size() > 1){
				int i;
				for(i = 0;i < lastuseval.size();++i){
					if(lastuseval[i].funcname == funct && lastuseval[i].var == funcorline[1]){
						lastuseval[i].line = funcorline[0];
						break;
					}
				}
				if(i >= lastuseval.size()){
					useloc varandline;
					varandline.funcname = funct;
					varandline.line = funcorline[0];
					varandline.var = funcorline[1];
					lastuseval.push_back(varandline);
				}
			}
		}
	}

	string holefuncname,linenum,var;

	sprintf(cmd,"llvm-dis %s.bc",filename.c_str());
	system(cmd);
	sprintf(cmd,"%s.ll",filename.c_str());
	llvmfilename=cmd;

	for(int lnum = 0;lnum < vline.size();++lnum){
		linetemp = vline[lnum];
		string holelinenum=to_string(linetemp);
		funcname = "";
		llvmNX.clear();
		ReadDataFromLlvmfile(llvmfilename,holelinenum,llvmNX,funcname);
		for(int i = 0;i < llvmNX.size(); ++i){
			llvmNX[i] = llvmNX[i].substr(0,llvmNX[i].find("!dbg"));
			llvmNX[i] = llvmNX[i].substr(0,llvmNX[i].find("#"));
		}
		vllvmNX.push_back(llvmNX);
		cout << funcname << " " << lnum << endl;
		vfuncname.push_back(funcname);
	}

	for (int i = 0,inum=0; i < vvp.size(); ++i)
	{
		holefuncname = vvp[i].funcname;
		linenum = vvp[i].line;
		string cri;
		for (int j = 0; j < vvp[i].var.size(); ++j)
		{
			cri +=linenum+":"+vvp[i].var[j];
			if(j<vvp[i].var.size()-1)
				cri+=",";
		}
		for(int j = 0;j < vvp[i].var.size();++j)
		{
			var = vvp[i].var[j];
			for(int k = 0;k < lastuseval.size();++k)
			{
				if(holefuncname == lastuseval[k].funcname && var == lastuseval[k].var){
					cri += ","+lastuseval[k].line+":"+var;
					break;
				}
			}
		}

		sprintf(cmd,"./llvm-slicer -c %s -entry %s -annotate slicer %s.bc ",
			cri.c_str(),holefuncname.c_str(),filename.c_str());inum++;
		cout<<cmd<<endl;

		system(cmd);

		cout<<endl;

		sprintf(cmd,"llvm-dis %s.sliced",filename.c_str());
		system(cmd);

		char filename1[2000]={};
		char filename2[2300]={};
		char filename3[2300]={};
		char filename0[2300]={};
		char filenamed[2300]={};
		char filenames[2300]={};

		sprintf(filenamed,"%s-debug.ll",filename.c_str());
		sprintf(filenames,"%s.sliced.ll",filename.c_str());

		sprintf(filename0,"%s_%d_%s_#%s#_[0].ll",filename.c_str(),inum,cri.c_str(),holefuncname.c_str());

		ifstream in( filenamed );
		while (getline(in, s))
		{
			if(s[0]!=';'&&s!=""&&s.substr(0,20)!="  ; SLICING CRITERIO")
			{
				v.push_back(s);
			}
		}
		ofstream out( filenamed );

		for (int j = 0; j < v.size(); ++j)
		{
			temp+=v[j];
			temp=temp+"\n";
		}

		out<<temp;

		for(int lnum = 0;lnum < vline.size();++lnum){
			funcname = vfuncname[lnum];
			llvmNX = vllvmNX[lnum];

			sprintf(filename1,"%s_%d_%s-debug.ll",filename.c_str(),inum,cri.c_str());
			sprintf(filename3,"%s_%d_%s.sliced.ll",filename.c_str(),inum,cri.c_str());
			sprintf(cmd,"cp %s %s",filenamed,filename1);
			system(cmd);
			sprintf(cmd,"cp %s %s",filenames,filename3);
			system(cmd);
			string funcnamesub=funcname.substr(funcname.rfind("@")+1,funcname.size());
			cout<<"holefuncname: "<<holefuncname<<endl<<"funcname:"<<funcnamesub<<endl << vline[lnum] << endl;
								
			if(!llvmNX.empty()&&holefuncname==funcnamesub){
				for (int ii = 0,kk=0; ii <v.size(); )
				{	
					if(v[ii][0]==' '&&llvmNX.size()!=1&&(v[ii] == llvmNX[kk] || v[ii].find(llvmNX[kk]) != string::npos))
					{
						ii++;kk++;
					}
					else 
					{
						ii++;kk=0;
					}
					if(kk==llvmNX.size())
					{
						int llvmline=ii-kk+1;
						sprintf(filename2,"%s_%d_%s_#%s#_[%d_%d].ll",filename.c_str(),inum,cri.c_str(),holefuncname.c_str(),llvmline,kk);     	
						rename(filename1,filename2);
						break;
					}
					if(kk==llvmNX.size()-1 && llvmNX.size()>=2 && v[ii]!=llvmNX[kk] && v[ii].find(llvmNX[kk]) == string::npos)
					{
						int llvmline=ii-kk+1;
						sprintf(filename2,"%s_%d_%s_#%s#_[%d_%d].ll",filename.c_str(),inum,cri.c_str(),holefuncname.c_str(),llvmline,kk);      	
						rename(filename1,filename2);
						break;
					}
					if(kk==llvmNX.size()-2 && llvmNX.size()>=3 && v[ii]!=llvmNX[kk] && v[ii].find(llvmNX[kk]) == string::npos)
					{
						int llvmline=ii-kk+1;
						sprintf(filename2,"%s_%d_%s_#%s#_[%d_%d].ll",filename.c_str(),inum,cri.c_str(),holefuncname.c_str(),llvmline,kk);     	
						rename(filename1,filename2);
						break;
					}
					if(kk==llvmNX.size()-3 && llvmNX.size()>=4 && v[ii]!=llvmNX[kk] && v[ii].find(llvmNX[kk]) == string::npos)
					{
						int llvmline=ii-kk+1;
						sprintf(filename2,"%s_%d_%s_#%s#_[%d_%d].ll",filename.c_str(),inum,cri.c_str(),holefuncname.c_str(),llvmline,kk);      	
						rename(filename1,filename2);
						break;
					}
					else if(ii==v.size()-1){
						rename(filename1,filename0);
			    		}
				}
			}
			else 
			{
				rename(filename1,filename0);
			}
			cout << endl;
		}
		v.clear();
		temp="";
		cout<<endl;		
	}
}
