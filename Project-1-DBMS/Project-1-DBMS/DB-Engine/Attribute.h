#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <vector>

class Attribute{
	private:
		const std::string ENDLIST = "ENDLIST"; //used to simplify Read function
		std::string Name;
		std::string VarType;
		std::vector<std::string> Data;
	public:
		//Constructors
		Attribute();
		Attribute(std::string name, std::string vartype, std::vector<std::string> data);
		Attribute(const Attribute& attribute);
		//Copy Assignment operator
		Attribute& operator = (const Attribute& attribute);
		
		//Getters and Setters
		
		std::string	Get_name() const;
		void  Set_name(std::string name);

		std::string  Get_vartype() const;
		void  Set_vartype(std::string vartype);
		
		void Clear_data();
		std::vector<std::string> Get_data() const;
		void Set_data(std::vector<std::string> data);

		std::string Get_value(unsigned int index) const;
		void Set_value(unsigned int index, std::string value);
		void Insert_value(std::string value);

		int Get_size() const;

		//Read and Write
		std::istream& Read(std::istream& is);
		std::ostream& Write(std::ostream& os);

		std::string& operator [](unsigned int i);
};



#endif