//#include<iostream>
//#include<Windows.h>
//using namespace std;
//int main() {
//	char color = '0'; char font = '0';
//	system("mode con cols=9001 lines=177");
//	while (1) {
//		string a = (string)"color " +color+++font;
//		system(a.c_str());
//		if (color>'9')color = '0';
//		Sleep(200);
//	}
//}
#import "C:/Program Files/Common Files/System/ado/msado15.dll"\no_namespace rename("EOF", "EndOfFile")
#include <iostream>
#include <iomanip>//for setw()
using namespace std;
class STU
{
public:
	char snum[10]; //ѧ�� 
	char sname[10]; //���� 
	char ssex[2]; //�ձ� 
	long sage; //���� 
	char smajor[20]; //רҵ 
public:
	STU() {}
	~STU() {}
};

int main()
{
	STU student;
	::CoInitialize(NULL); // ��ʼ��OLE/COM�⻷�� ��Ϊ����ADO�ӿ���׼��

	_RecordsetPtr m_pRecordset("ADODB.Recordset");
	_ConnectionPtr m_pConnection("ADODB.Connection");

	_bstr_t bstrSQL("select * from stu_info"); //��ѯ��� 
	char * query_cmd = "DELETE FROM stu_info WHERE sname = '������'";

	try
	{
		// ����Connection����
		m_pConnection.CreateInstance("ADODB.Connection");
		// ���������ַ�����������BSTR�ͻ���_bstr_t����
		_bstr_t strConnect = "Provider=SQLOLEDB;Server=(local);Database=student; uid=sa; pwd=123;";
		//�����ݿ�����������ServerΪ����(192.168.1.5,3340)
		//�û�sa������123ֻ������ҵĿ� 
		m_pConnection ->Open(strConnect, "", "", adModeUnknown);
		if (m_pConnection == NULL)
			cerr<<"Lind data ERROR!\n";
		// ������¼������
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		// ȡ�ñ��еļ�¼
		m_pRecordset - >Open(bstrSQL, m_pConnection.GetInterfacePtr(),
			adOpenDynamic, adLockOptimistic, adCmdText);

		_variant_t vsnum, vsname, vsage, vssex, vsmajor; //��Ӧ���е�snum,sname,sage,ssex,smajor
		cout<< "ѧ�� ���� ���� �ձ� רҵ";
		cout<< "\n----------------------------------------------------------------\n";

		while (!m_pRecordset ->EndOfFile)
		{
			vsnum = m_pRecordset ->GetCollect(_variant_t((long)0));//������ֶα�ź��ֶ��������� 
			vsname = m_pRecordset ->GetCollect("sname");
			vsage = m_pRecordset ->GetCollect("sage");
			vssex = m_pRecordset ->GetCollect("ssex");
			vsmajor = m_pRecordset ->GetCollect("smajor");
			if (vsnum.vt != VT_NULL && vsname.vt != VT_NULL && vsage.vt != VT_NULL
				&& vssex.vt != VT_NULL && vsmajor.vt != VT_NULL)
			{
				cout.setf(ios::left);
				cout << setw(14)<<(char*)(_bstr_t)vsnum;
				cout << setw(14)<<(char*)(_bstr_t)vsname;
				cout << setw(8)<< vsage.lVal;
				cout << setw(8)<<(char*)(_bstr_t)vssex;
				cout<<setw(20)<<(char*)(_bstr_t)vsmajor;
				cout.unsetf(ios::left);
				cout<< endl;
			}
			m_pRecordset - >MoveNext(); ///�Ƶ���һ����¼
		}
		cout << "\n----------------------------------------------------------------\n";
		cout << "\n��������Ҫ��ӵ�ѧ����Ϣ\n";
		cout << "ѧ��:";
		cin >> student.snum;
		cout<< "\n����:";
		cin >> student.sname;
		cout<< "\n����:";
		cin >> student.sage;
		cout<< "\n�ձ�:";
		cin >> student.ssex;
		cout<< "\nרҵ:";
		cin >> student.smajor;
		m_pRecordset - >MoveFirst(); //�ƶ�����һ����¼
		m_pRecordset - >AddNew(); ///����¼�¼
		m_pRecordset - >PutCollect("snum", _variant_t(student.snum));
		m_pRecordset - >PutCollect("sname", _variant_t(student.sname));
		m_pRecordset - >PutCollect("sage", _variant_t(student.sage));
		m_pRecordset - >PutCollect("ssex", _variant_t(student.ssex));
		m_pRecordset - >PutCollect("smajor", _variant_t(student.smajor));
		m_pRecordset - >Update();

		m_pConnection - >Execute(query_cmd, NULL, 1); //��Executeִ��sql�����ɾ��
		m_pRecordset - >Close(); // �رռ�¼��
	}

	// ��׽�쳣
	catch (_com_error e)
	{
		// ��ʾ������Ϣ
		cerr<< "\nERROR:"<<(char*)e.Description();//�׳��쳣
	}
	if (m_pConnection - >State)
		m_pConnection - >Close();

	::CoUninitialize();

	return 0;
}