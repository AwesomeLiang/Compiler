#include "assembler.h"
#include "dag.h"
#include <sstream>

using std::to_string;
using std::stringstream;

string int_to_hex_string(int num) {
	stringstream stream;
	stream << std::hex << num;
	return stream.str();
}

int Assembler::label;
int Assembler::pos;
int Assembler::fun;

// ���캯��
Assembler::Assembler() {
	Register eax, ebx, ecx, edx, rm;  // �ֱ��ӦEAX, EBX, M(Memory �Ƿ����ڴ���)
	registers.push_back(eax);
	registers.push_back(ebx);
	registers.push_back(ecx);
	registers.push_back(edx);
	registers.push_back(rm);
	//Node a("a", v), b("b", v);
	//registers[0].add(a);
	//registers[1].add(b);
	//regValue[ra] = "";
	//regValue[rb] = "";
	memset(jmpTable, -1, sizeof(jmpTable));
	isGlobal = true;
	inFunc = false;
	tmpLength = 0;
	paraLength = 4;
	isDataStart = true;
	isCodeStart = true;
}

bool Exchangeable(tag op) {
	if (op == ADD || op == MUL) {
		return true;
	}
	return false;
}


// �ж��Ƿ����ĸ��Ĵ�������ĳһ������������򷵻��Ǹ��Ĵ��������û�У��򷵻�-1
int Assembler::hasVar(Node var) {
	for (auto it = registers.begin(); it != registers.end() - 1; ++it) {
		if ((*it).hasVar(var)) {
			return it - registers.begin();
		}
	}
	return -1;
}

// �ж��Ƿ����ĸ��Ĵ����ǿյģ����ؿյļĴ����±꣬���򷵻�-1
int Assembler::hasEmpty() {
	for (auto it = registers.begin(); it != registers.end() - 1; ++it) {
		if ((*it).empty()) {
			return it - registers.begin();
		}
	}
	return -1;
}

// �������
void Assembler::insert(Node &var) {
	if (activeTable.find(var) != activeTable.end()) {  // �Ѿ��ڱ�����
		return;
	}
	else if (var.isTempVar()) {  // Ϊ��ʱ����
		activeTable[var] = false;
	}
	else if (var.isVar()) {  // ����ʱ����
		activeTable[var] = true;
	}
	return;
}

// Ѱ�ұ����洢�ļĴ���
int Assembler::locRegister(Node &n) {
	//if (n.cat == none) {
	//	return -1;
	//}
	for (auto it = registers.begin(); it != registers.end(); it++) {
		if ((*it).hasVar(n)) {
			return it - registers.begin();
		}
	}
	return -1;

}

// ��ʼ����Ծ��
void Assembler::initTable(vector<quaternary> &block) {
	int length = registers.size();
	for (auto it : block) {
		// ���������飬�����еı�����������У��������ʱ����������ΪFalse������ΪTrue
		insert(it.arg1);
	//	if (it.arg1.isVar()) {
	//		registers[length - 1].add(it.arg1);
	//	}
		insert(it.arg2);
	//	if (it.arg2.isVar()) {
	//		registers[length - 1].add(it.arg2);
	//	}
		insert(it.result);
	//	if (it.result.isVar()) {
	//		registers[length - 1].add(it.result);
	//	}
	}
	//show();
}

void Assembler::fillTable(vector<quaternary>& block)
{
	for (auto it = block.rbegin(); it != block.rend(); ++it) {
		if ((*it).arg1.isVar() || (*it).arg1.isTempVar()) {  // �Ǳ���
			(*it).activeArg1 = activeTable.at((*it).arg1);
			if ((*it).activeArg1 == false) {
				activeTable[(*it).arg1] = true;
			}  // �����ʱ����Ծ�����ڱ��иĳɻ�Ծ
		}
		if ((*it).arg2.isVar() || (*it).arg2.isTempVar()) {  // �Ǳ���
			(*it).activeArg2 = activeTable.at((*it).arg2);
			if ((*it).activeArg2 == false) {
				activeTable[(*it).arg2] = true;
			}  // �����ʱ����Ծ�����ڱ��иĳɻ�Ծ
		}
		if ((*it).result.isVar() || (*it).result.isTempVar()) {  // �Ǳ���
			(*it).activeRes = activeTable.at((*it).result);
			activeTable[(*it).result] = ~(*it).activeRes;
		}
		//show(); // debug�ã��鿴��Ծ��
	}
}

void Assembler::codegen(vector<quaternary> &block) {
	for (auto it : block) {
		if (it.op == ASSIGN) {
			if (it.arg1.kindNode == 3 && it.arg1.attributeNode.attributeId.cat == f) {
				insertCode("mov", getAddr(it.arg1), registerName[0], "");
			}
			if (it.result.isMember()) {
				if (addressMap.count(it.result) != 1) {
					int baseAddr = asMap[it.result.getNodeStruct()];
					int address = baseAddr - it.result.offset;
					cout << it.result << it.result.length << endl;
					if (it.result.length == 1) {
						addressMap[it.result.length] = "b [ebp-0" + int_to_hex_string(address) + "h]";
					}
					else if (it.result.length > 1 && it.result.length <= 2) {
						addressMap[it.result] = "w [ebp-0" + int_to_hex_string(address) + "h]";
					}
					else if (it.result.length > 2 && it.result.length <= 4) {
						addressMap[it.result] = "d [ebp-0" + int_to_hex_string(address) + "h]";
					}
					else if (it.result.length > 4 && it.result.length <= 8) {
						addressMap[it.result] = "q [ebp-0" + int_to_hex_string(address) + "h]";
					}
					else if (it.result.length > 8 && it.result.length <= 16) {
						addressMap[it.result] = "s [ebp-0" + int_to_hex_string(address) + "h]";
					}
				}
				if (it.arg1.isConstant()) {
					insertCode("mov", getAddr(it.result), to_string(it.arg1.attributeNode.attributeInt), "");
				}
				else if (locRegister(it.arg1) != -1) {
					insertCode("mov", getAddr(it.result), registerName[locRegister(it.arg1)], "");
				}
				else {
					insertCode("mov", getAddr(it.result), getAddr(it.arg1), "");
				}
				//continue;
			}
			else if (it.arg1.isMember()) {
				if (addressMap.count(it.arg1) != 1) {
					int baseAddr = asMap[it.arg1.getNodeStruct()];
					int address = baseAddr - it.result.offset;
					cout << it.result << it.result.length << endl;
					if (it.arg1.length == 1) {
						addressMap[it.arg1] = "b [ebp-0" + int_to_hex_string(address) + "h]";
					}
					else if (it.arg1.length > 1 && it.arg1.length <= 2) {
						addressMap[it.arg1] = "w [ebp-0" + int_to_hex_string(address) + "h]";
					}
					else if (it.arg1.length > 2 && it.arg1.length <= 4) {
						addressMap[it.arg1] = "d [ebp-0" + int_to_hex_string(address) + "h]";
					}
					else if (it.arg1.length > 4 && it.arg1.length <= 8) {
						addressMap[it.arg1] = "q [ebp-0" + int_to_hex_string(address) + "h]";
					}
					else if (it.arg1.length > 8 && it.arg1.length <= 16) {
						addressMap[it.arg1] = "s [ebp-0" + int_to_hex_string(address) + "h]";
					}
				}
				if (locRegister(it.result) != -1 && locRegister(it.result) != registers.size() - 1) {
					insertCode("mov", registerName[locRegister(it.result)], getAddr(it.arg1), "");
				}
				else {
					insertCode("mov", registerName[0], getAddr(it.arg1), "");
					insertCode("mov", getAddr(it.result), registerName[0], "");
					registers[0].clear();
					registers[0].add(it.result);
					registers[0].add(it.arg1);
				}
				continue;

			}
			else {
				assignment(it);
			}
		}
		else if (it.op == ADD || it.op == SUB || it.op == MUL || it.op == DIV) {
			arithmetic(it);
		}
		else if (it.op == WHILE) {
			insertCode("mov", registerName[0], getAddr(it.arg1), "");
			insertCode("and", registerName[0], registerName[0], "");
			registers[0].clear();
			if (jmpTable[it.pointJmp] != -1) { // ����Ѿ���¼��label���
				jmpTable[it.pointJmp] = label;
				insertCode("jz", "<label" + to_string(jmpTable[it.pointJmp]), "", "");
			}
			else {
				jmpTable[it.pointJmp] = label;
				insertCode("jz", ">label" + to_string(label++), "", "");
			}
		}
		else if (it.op == GOTO) {
			if (jmpTable[it.pointJmp] != -1) {
				insertCode("jz", "<label" + to_string(jmpTable[it.pointJmp]), "", "");
			}
			else {
				jmpTable[it.pointJmp] = label;
				insertCode("jz", ">label" + to_string(label++), "", "");
			}
		}
		else if (it.op == IF) {
			insertCode("mov", registerName[0], getAddr(it.arg1), "");
			insertCode("and", registerName[0], registerName[0], "");
			registers[0].clear();
			if (jmpTable[it.pointJmp] != -1) { // ����Ѿ���¼��label���
				jmpTable[it.pointJmp] = label;
				insertCode("jz", "<label" + to_string(jmpTable[it.pointJmp]), "", "");
			}
			else {
				jmpTable[it.pointJmp] = label;
				insertCode("jz", ">label" + to_string(label++), "", "");
			}
		}
		else if (it.op == LABEL) {
			if (jmpTable[pos] != -1) {
				insertCode("", "", "", "label" + to_string(jmpTable[pos]) + ":");
			}
			else {
				jmpTable[pos] = label;
				insertCode("", "", "", "label" + to_string(label++) + ":");
			}
		}
		else if (it.op == STARTF) {
			if (isCodeStart) {
				insertCode("", "", "", ".code");
				isCodeStart = false;
			}
			inFunc = true;
			//insertCode("", "", "", "label" + to_string(jmpTable[pos]));
			if (it.arg1.attributeNode.attributeId.name == "main") {
				callMain();
				isGlobal = false;
			}
			else {
				funMap[it.arg1] = fun;
				insertCode("", "", "", "func" + to_string(fun++) + ":");
				startFunction();
				auto vec = it.arg1.getParamNodeVector();
				cout << vec.size();
				for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
					declareVn(*it);
				}
				//show();
			}

		}
		else if (it.op == DECLAREI) {
			if (isDataStart && !inFunc) {
				insertCode("", "", "", ".data");
				isDataStart = false;
			}
			if (isGlobal && !inFunc) {
				string type;
				if (it.arg1.length == 1) {
					type = "db";
				}
				else if (it.arg1.length == 2) {
					type = "dd";
				}
				else if (it.arg1.length == 4) {
					type = "dw";
				}
				else {
					type = "dq";
				}
				insertCode(type, "0", "", it.arg1.attributeNode.attributeId.name);
				pos++;
				addressMap[it.arg1] = it.arg1.attributeNode.attributeId.name;
				continue;
			}
			declare(it);
		}
		else if (it.op == DECLAREA || it.op == DECLARES) {
			declareAS(it);
		}
		else if (it.op == ENDF) {
			endFunction();
			inFunc = false;
			//paraLength = 4;
			insertCode("ret", "", "", "");
		}
		else if (it.op == SHIFT) {
			if (it.result.isEndOfArray()) { // ��������ײ�
				//insertCode("mov", registerName[0], getAddr(it.arg1), "");
				if (it.arg2.isConstant()) {
					int base = asMap[it.arg1];
					int address = base - it.arg2.attributeNode.attributeInt * it.result.length;
					registers[0].clear();
					string addr;

					if (it.arg2.length == 1) {
						addr = "b [ebp-0" + int_to_hex_string(address) + "h]";
					}
					else if (it.arg2.length > 1 && it.arg2.length <= 2) {
						addr = "w [ebp-0" + int_to_hex_string(address) + "h]";
					}
					else if (it.arg2.length > 2 && it.arg2.length <= 4) {
						addr = "d [ebp-0" + int_to_hex_string(address) + "h]";
					}
					else if (it.arg2.length > 4 && it.arg2.length <= 8) {
						addr = "q [ebp-0" + int_to_hex_string(address) + "h]";
					}
					else if (it.arg2.length > 8 && it.arg2.length <= 16) {
						addr = "s [ebp-0" + int_to_hex_string(address) + "h]";
					}

					addressMap[it.result] = addr;

					//insertCode("mov", addr, getAddr(it.arg1), "");
				}
				//insertCode("mov", registerName[0], getAddr())
			}
			else {
				//registers[0].clear();
				//insertCode("add", registerName[1], registerName[0], "");
				//insertCode("mov", registerName[0], getAddr(it.arg2), "");
				//insertCode("imul", registerName[0], to_string(it.result.length), "");
				//insertCode("mov", registerName[1], registerName[0], "");
			}
			//if()
			//insertCode("mul", registerName[0], getAddr(Node(it.result.length)), "");
		}
		else if (it.op == PARAM) {
			stackDepth += it.arg1.length;
			if (it.arg1.isConstant()) {
				insertCode("push", int_to_hex_string(it.arg1.attributeNode.attributeInt), "", "");
			}
			else {
				insertCode("mov", registerName[0], getAddr(it.arg1), "");
				insertCode("push", registerName[0], "", "");
			}
		}
		else if (it.op == CALL) {
			insertCode("jmp", "func" + to_string(funMap[it.arg1]), "", "");
			insertCode("add", "esp", int_to_hex_string(stackDepth), "");
			stackDepth = 0;
		}
		else if (it.op == POINT) {
			if(it.result.isMember()) {
				if (addressMap.count(it.result) != 1) {
					int baseAddr = asMap[it.result.getNodeStruct()];
					int address = baseAddr - it.result.offset;
					if (it.result.length == 1) {
						addressMap[it.result.length] = "b [ebp-0" + int_to_hex_string(address) + "h]";
					}
					else if (it.result.length > 1 && it.result.length <= 2) {
						addressMap[it.result] = "w [ebp-0" + int_to_hex_string(address) + "h]";
					}
					else if (it.result.length > 2 && it.result.length <= 4) {
						addressMap[it.result] = "d [ebp-0" + int_to_hex_string(address) + "h]";
					}
					else if (it.result.length > 4 && it.result.length <= 8) {
						addressMap[it.result] = "q [ebp-0" + int_to_hex_string(address) + "h]";
					}
					else if (it.result.length > 8 && it.result.length <= 16) {
						addressMap[it.result] = "s [ebp-0" + int_to_hex_string(address) + "h]";
					}
				}
				if (it.arg1.isConstant()) {
					insertCode("mov", getAddr(it.result), to_string(it.arg1.attributeNode.attributeInt), "");
				}
				else if (locRegister(it.arg1) != -1) {
					insertCode("mov", getAddr(it.result), registerName[locRegister(it.arg1)], "");
				}
				else {
					insertCode("mov", getAddr(it.result), getAddr(it.arg1), "");
				}
			}
		}
		else if (it.op == RETURN) {
			if (it.arg1 != Node()) {
				insertCode("mov", registerName[0], getAddr(it.arg1), "");
			}

		}
		else if (it.op == ASM) {
			insertCode(it.arg1.strAsm, "", "", "");
		}
		//show();
		pos++;
	}

	// �ڻ�����Ľ����ͷżĴ���
	for (auto itReg : vector<Register>(registers.begin(), registers.end()- 1)) {
		itReg.clear();
	}
	//endMain();

}

void Assembler::show() {
	cout << "Active Table" << endl;
	for (auto it : activeTable) {
		cout << it.first << " ";
		string ok;
		it.second ? ok = "Yes" : ok = "No";
		cout << ok << endl;
	}
	cout << endl;
	cout << "Register Table" << endl;
	for (auto it = registers.begin(); it != registers.end(); ++it) {
		cout << registerName[it - registers.begin()] << endl;
		it->show();
		cout << endl;
	}
	cout << "Address Table" << endl;
	for (auto it : addressMap) {
		cout << it.first << ": " << it.second << endl;
	}
}

void Assembler::clear() {
	for (auto it = activeTable.begin(); it != activeTable.end(); it) {
		auto node = it->first;
		if (node.isVar()) {
			it++;
		}
		else {
			it = activeTable.erase(it);
		}
	}
	for (auto it = activeTable.begin(); it != activeTable.end(); it) {
		auto node = it->first;
		if (node.isVar()) {
			it++;
		}
		else {
			it = activeTable.erase(it);
		}
	}
}

// Ѱ�ҼĴ������� qd:(w, B, C, A)
tuple<int, int, int> Assembler::getRegister(quaternary &qd) {
	int locIndex = locRegister(qd.arg1);
	int locIndex2 = locRegister(qd.arg2);
	int emptyIndex = hasEmpty(); // Rj
	int length = registers.size();

	if (locIndex != -1 && registers[locIndex].size() == 1 && locIndex != length - 1) { // ����Ri�� Riֻ��B
		if (qd.activeArg1 == true && (qd.arg1 != qd.result) || registers[length - 1].hasVar(qd.arg1) == false) {
			if (emptyIndex != -1 && emptyIndex != length - 1) { // ���ڿռĴ���Rj
				//ST(registers[emptyIndex], registers[locIndex]); // ���� ST Rj, Rj(Ri -> Rj)
				//std::cout << "mov" << registerName[emptyIndex] << ", " << registerName[locIndex] << endl;
				insertCode("mov", registerName[emptyIndex], registerName[locIndex], "");
				registers[locIndex].add(qd.arg1);
			}
			else {
				//ST([arg1], registers[locIndex]); // ���� ST [B], Ri(Ri -> B)
				insertCode("mov", getAddr(qd.arg1), registerName[locIndex], "");
				//std::cout << "ST" << qd.arg1 << ", Reg" << locIndex << endl;
				
				registers[length - 1].add(qd.arg1);
			}
		}
		registers[locIndex].remove(qd.arg1); // Ri��ȥ��B
		return make_tuple(locIndex, locIndex, locRegister(qd.arg2));
	}
	else if (locIndex2 != -1 && registers[locIndex2].size() == 1 && locIndex2 != length - 1 && Exchangeable(qd.op)) {
		quaternary tempQd(qd.op, qd.arg2, qd.arg1, qd.result); // ����B, C
		return getRegister(tempQd);
	}
	else if (emptyIndex != -1 && emptyIndex != length - 1) { // ���ڿռĴ���Rj
		return make_tuple(emptyIndex, locIndex, locRegister(qd.arg2));
	}
	else {
		int compelIndex = 0; // ǿ���ͷ�����
		for (int i = 0; i < registers[compelIndex].size(); ++i) {
			registers[length - 1].add(registers[compelIndex].getElement(i));
		}
		registers[compelIndex].clear();
		return make_tuple(compelIndex, locIndex, locRegister(qd.arg2));
	}
}

void Assembler::arithmetic(quaternary &qd) {
	auto triIndex = getRegister(qd);
	int regIndex = get<0>(triIndex);
	int arg1Index = get<1>(triIndex);
	int arg2Index = get<2>(triIndex);
	int length = registers.size();

	if (regIndex != arg1Index) {
		//LD(registers[regIndex], registers[arg1Index]) //LD R, [B]
		//cout << "LD " << " Reg" << regIndex << ", " << qd.arg1 << endl;
		insertCode("mov", registerName[regIndex], getAddr(qd.arg1), "");
		//op(registers[regIndex], registers[arg2Index]) // OP R, [C]
		//cout << operatorMap[qd.op] << " Reg" << regIndex << ", " << qd.arg2 << endl;
		if (qd.arg2.isConstant()) {
			insertCode(operatorMap[qd.op], registerName[regIndex], to_string(qd.arg2.attributeNode.attributeInt), "");
		}
		else {
			if (arg2Index != length - 1) {
				insertCode(operatorMap[qd.op], registerName[regIndex], registerName[arg2Index], "");
			}
			else {
				insertCode(operatorMap[qd.op], registerName[regIndex], getAddr(qd.arg2), "");
			}
			//else {
			//	////insertCode("mov", "")
			//	//int newIndex = (regIndex == 0) ? 1 : 0;
			//	//insertCode("mov", registerName[newIndex], getAddr(qd.arg2), "");
			//	//insertCode(operatorMap[qd.op], registerName[regIndex], registerName[newIndex], "");
			//	//registers[newIndex].clear();
			//	//registers[newIndex].add(qd.arg2);
			//}
		}
	}
	else {
		//op(registers[regIndex], registers[arg2Index]) // OP R, [C]
		//cout << operatorMap[qd.op] << " Reg" << regIndex << ", " << qd.arg2 << endl;
		if (qd.arg2.isConstant()) {
			insertCode(operatorMap[qd.op], registerName[regIndex], to_string(qd.arg2.attributeNode.attributeInt), "");
		}
		else {
			insertCode(operatorMap[qd.op], registerName[regIndex], registerName[arg2Index], "");
		}
	}
	if (qd.result.isVar()) {
		insertCode("mov", getAddr(qd.result), registerName[regIndex], "");
	}
	for (auto itReg : registers) {
		itReg.remove(qd.result);
	}
	registers[regIndex].add(qd.result);
}

void Assembler::assignment(quaternary &qd) {

	if (qd.arg1.isConstant()) {
		insertCode("mov", getAddr(qd.result), to_string(qd.arg1.attributeNode.attributeInt), "");
		return;
	}

	auto triIndex = getRegister(qd);
	int regIndex = get<0>(triIndex);
	int arg1Index = get<1>(triIndex);
	int arg2Index = get<2>(triIndex);

	//cout << "R':" << regIndex << endl;
	//cout << "B':" << arg1Index << endl;
	//cout << "C':" << arg2Index << endl;



	if (regIndex != arg1Index) {
		//LD(registers[regIndex], registers[arg1Index]) //LD R, B
		insertCode("mov", registerName[regIndex], getAddr(qd.arg1), "");
		insertCode("mov", getAddr(qd.result), registerName[regIndex], "");
	}
	for (auto itReg : registers) {
		itReg.remove(qd.result);
	}
	registers[regIndex].add(qd.result);
}

void Assembler::logic(quaternary &qd) {
	auto triIndex = getRegister(qd);
	int regIndex = get<0>(triIndex);
	int arg1Index = get<1>(triIndex);
	int arg2Index = get<2>(triIndex);

	if (regIndex != arg1Index) {
		//LD(registers[regIndex], registers[arg1Index]) //LD R, [B]
		//cout << "LD " << " Reg" << regIndex << ", " << qd.arg1 << endl;
		insertCode("mov", registerName[regIndex], getAddr(qd.arg1), "");
		//op(registers[regIndex], registers[arg2Index]) // OP R, [C]
		cout << operatorMap[qd.op] << " Reg" << regIndex << ", " << qd.arg2 << endl;
		insertCode(operatorMap[qd.op], registerName[regIndex], getAddr(qd.arg2), "");
	}
	else {
		//op(registers[regIndex], registers[arg2Index]) // OP R, [C]
		//cout << operatorMap[qd.op] << " Reg" << regIndex << ", " << qd.arg2 << endl;
		insertCode(operatorMap[qd.op], registerName[regIndex], getAddr(qd.arg2), "");
	}

	for (auto itReg : registers) {
		itReg.remove(qd.result);
	}
	registers[regIndex].add(qd.result);
}

// ���ú�����ʼʱ�Ļ��
void Assembler::startFunction() {
	insertCode("push", "ebp", "", "");
	insertCode("mov", "ebp", "esp", "");
	insertCode("sub", "esp", "0ffh", ""); // �̶�ֵ
	insertCode("push", "ebx", "", "");
	insertCode("push", "esi", "", "");
	insertCode("push", "edi", "", "");
	insertCode("lea", "edi", "[ebp-0ffh]", ""); // �̶�ֵ
}

void Assembler::endFunction() {
	insertCode("pop", "edi", "", "");
	insertCode("pop", "esi", "", "");
	insertCode("pop", "ebx", "", "");
	insertCode("add", "esp", "0ffh", ""); // �̶�ֵ
	insertCode("pop", "ebp", "", "");
}

void Assembler::callMain() {
	insertCode("", "", "", "start:");
	insertCode("push", "ebp", "", "");
	insertCode("mov", "ebp", "esp", "");
	insertCode("sub", "esp", "0ffh", ""); // �̶�ֵ
	insertCode("push", "ebx", "", "");
	insertCode("push", "esi", "", "");
	insertCode("push", "edi", "", "");
	insertCode("lea", "edi", "[ebp-0ffh]", ""); // �̶�ֵ
	//insertCode("mov", "ecx", "10h", "");
	//insertCode("mov", "eax", "0cccccccch", "");
	//insertCode("rep", "stos", "d [edi]", "");
}

void Assembler::endMain() {
	insertCode("pop", "edi", "", "");
	insertCode("pop", "esi", "", "");
	insertCode("pop", "ebx", "", "");
	insertCode("add", "esp", "0ffh", ""); // �̶�ֵ
	insertCode("pop", "ebp", "", ""); 
}

void Assembler::insertCode(Asm a) {
	dest.push_back(a);
}

void Assembler::insertCode(string op, string arg1, string arg2, string label) {
	dest.push_back(Asm(op, arg1, arg2, label));
}


string Assembler::getAddr(Node &n) {
	if (addressMap.count(n) != 1) { // �������������
		tmpLength += n.length;
		addressMap[n] = "d [ebp-0" + int_to_hex_string(tmpLength) + "h]";
		auto length = registers.size();
		registers[length - 1].add(n);
		return addressMap[n];
	}
	else {
		return addressMap[n];
	}
}

void Assembler::declareVn(Node &n) {
	int length = registers.size();
	if (n.length == 1) {
		addressMap[n] = "b [ebp-0" + int_to_hex_string(paraLength) + "h]";
		paraLength += 1;
	}
	else if (n.length > 1 && n.length <= 2) {
		addressMap[n] = "w [ebp+0" + int_to_hex_string(paraLength) + "h]";
		paraLength += 2;
	}
	else if (n.length > 2 && n.length <= 4) {
		addressMap[n] = "d [ebp+0" + int_to_hex_string(paraLength) + "h]";
		paraLength += 4;
	}
	else if (n.length > 4 && n.length <= 8) {
		addressMap[n.length] = "q [ebp+0" + int_to_hex_string(paraLength) + "h]";
		paraLength += 8;
	}
	else if (n.length > 8 && n.length <= 16) {
		addressMap[n] = "s [ebp+0" + int_to_hex_string(paraLength) + "h]";
		paraLength += 16;
	}
	else {
		//cout << "NOT" << n.length << endl;
	}

	registers[length - 1].add(n);
	//cout << length - 1 << endl;
}


void Assembler::declare(quaternary &qd) { // ����
	int length = registers.size();

	if (qd.arg1.length == 1) {
		tmpLength += 1;
		addressMap[qd.arg1] = "b [ebp-0" + int_to_hex_string(tmpLength) + "h]";
	}
	else if (qd.arg1.length > 1 && qd.arg1.length <= 2) {
		tmpLength += 2;
		addressMap[qd.arg1] = "w [ebp-0" + int_to_hex_string(tmpLength) + "h]";
	}
	else if (qd.arg1.length > 2 && qd.arg1.length <= 4) {
		tmpLength += 4;
		addressMap[qd.arg1] = "d [ebp-0" + int_to_hex_string(tmpLength) + "h]";
	}
	else if (qd.arg1.length > 4 && qd.arg1.length <= 8) {
		tmpLength += 8;
		addressMap[qd.arg1] = "q [ebp-0" + int_to_hex_string(tmpLength) + "h]";
	}
	else if (qd.arg1.length > 8 && qd.arg1.length <= 16) {
		tmpLength += 16;
		addressMap[qd.arg1] = "s [ebp-0" + int_to_hex_string(tmpLength) + "h]";
	} //

	registers[length - 1].add(qd.arg1); // �����ڴ�
}


void Assembler::declareAS(quaternary &qd) { // ����������߽ṹ��
	int length = registers.size();

	if (qd.arg1.length == 1) {
		tmpLength += 1;
		addressMap[qd.arg1] = "b [ebp-0" + int_to_hex_string(tmpLength) + "h]";
	}
	else if (qd.arg1.length > 1 && qd.arg1.length <= 2) {
		tmpLength += 2;
		addressMap[qd.arg1] = "w [ebp-0" + int_to_hex_string(tmpLength) + "h]";
	}
	else if (qd.arg1.length > 2 && qd.arg1.length <= 4) {
		tmpLength += 4;
		addressMap[qd.arg1] = "d [ebp-0" + int_to_hex_string(tmpLength) + "h]";
	}
	else if (qd.arg1.length > 4 && qd.arg1.length <= 8) {
		tmpLength += 8;
		addressMap[qd.arg1] = "q [ebp-0" + int_to_hex_string(tmpLength) + "h]";
	}
	else if (qd.arg1.length > 8 && qd.arg1.length <= 16) {
		tmpLength += 16;
		addressMap[qd.arg1] = "s [ebp-0" + int_to_hex_string(tmpLength) + "h]";
	}
	else {
		tmpLength += qd.arg1.length;
	}

	asMap[qd.arg1] = tmpLength;

	registers[length - 1].add(qd.arg1); // �����ڴ�
}


void Assembler::showCode() {
	for (auto it : dest) {
		if (it.label != "") {
			cout << it.label << " ";
		}
		cout << it.op;
		if (it.arg1 != "") {
			cout << " " << it.arg1;
		}
		if (it.arg2 != "") {
			cout << ", " << it.arg2;
		}
		cout << endl;
	}
}

void Assembler::showCode(ostream& os) {
	for (auto it : dest) {
		if (it.label != "") {
			os << it.label << " ";
		}
		os << it.op;
		if (it.arg1 != "") {
			os << " " << it.arg1;
		}
		if (it.arg2 != "") {
			os << ", " << it.arg2;
		}
		os << endl;
	}
}