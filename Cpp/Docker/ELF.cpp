#include "../../H/Docker/ELF.h"

// Returns true if the ELF-file is 32-bit, otherwise false
bool ELF::Get_Bits_Size(uint8_t* buffer)
{
   return reinterpret_cast<elf32_hdr*>(buffer)->e_ident[EI_CLASS] == 1;
}

uint64_t ELF::Get_Section_Header_Offset(uint8_t* buffer)
{
	return Get_Bits_Size(buffer) ? reinterpret_cast<elf32_hdr*>(buffer)->e_shoff : reinterpret_cast<elf64_hdr*>(buffer)->e_shoff;
}

uint64_t ELF::Get_Header_Amount(uint8_t* buffer)
{
	return Get_Bits_Size(buffer) ? reinterpret_cast<elf32_hdr*>(buffer)->e_shnum : reinterpret_cast<elf64_hdr*>(buffer)->e_shnum;
}

vector<string> ELF::Get_Section_Names(uint8_t* buffer) {
    bool BIT_SIZE = Get_Bits_Size(buffer);
    uint16_t Index = Get_Bits_Size(buffer) ? reinterpret_cast<elf32_hdr*>(buffer)->e_shstrndx : reinterpret_cast<elf64_hdr*>(buffer)->e_shstrndx;
    uint64_t Current_Section_Header = Get_Section_Header_Offset(buffer);
    uint64_t Header_Count = Get_Header_Amount(buffer);
    vector<string> Names;

    if (BIT_SIZE) {
        elf32_shdr* Section_Headers = reinterpret_cast<elf32_shdr*>(&buffer[Current_Section_Header]);
        elf32_shdr& Section_Header = Section_Headers[Index];

        /*
            Made by Joonas Lehto 13/05/2020
              Master header:
              is x86 or x86-64
        | <-- sh_offset: int
              e_shstrndx: int (INDEX) = 31
        |
        |
        |
        |
        |-->  First Section Header:

              type: int
              name: int (index)

              .
              .
              .

              .rdata Section Header: (30)
              type: int
              name: int (index) = 2

              .rdata Section Header: (31)
              type: int
              name: int (index) = 2

              .
              .
              .

              TARGET e_shstrndx (31)
              type: int
              name: int (index)
              position: int (pointer)


              .
              .
              .

              Last Section Header:

              type: int
              name: int (index)









   2443FG F DF
  3qerFEF
  REFRFE
  WEF W FR  _glfwInit \0



  wdwwd                                                    0        1        2
  dwdwwwwwwwwwwwwwwgrrfrfefe ...........dw  3 r3rr  4 3 -> .text \0 .data \0 .rdata \0 => { .text, .data, .rdata }




        */

        uint8_t* position = reinterpret_cast<uint8_t*>(&buffer[Section_Header.sh_offset]);

        string type = "";
        for (int i = 0; i < Section_Header.sh_size; i++)
        {
            if (position[i] == 0) {
                Names.push_back(type);
                type = "";
                continue;
            }
            type.push_back(position[i]);
        }
    }
    else
    {
        //this summer coming soon!
        elf64_shdr* Section_Headers = reinterpret_cast<elf64_shdr*>(&buffer[Current_Section_Header]);
        elf64_shdr& Section_Header = Section_Headers[Index];

        uint8_t* position = reinterpret_cast<uint8_t*>(&buffer[Section_Header.sh_offset]);

        string type = "";
        for (int i = 0; i < Section_Header.sh_size; i++)
        {
            if (position[i] == 0) {
                Names.push_back(type);
                type = "";
                continue;
            }
            type.push_back(position[i]);
        }
    }
    return Names;
}

uint64_t ELF::Find_Section(uint8_t* buffer, string type) {
    bool BIT_SIZE = Get_Bits_Size(buffer);
    uint64_t Current_Section_Header = Get_Section_Header_Offset(buffer);
    uint64_t Header_Count = Get_Header_Amount(buffer);

    vector<string> Names = Get_Section_Names(buffer);

    if (BIT_SIZE) {
        elf32_shdr* Section_Headers = reinterpret_cast<elf32_shdr*>(&buffer[Current_Section_Header]);
        for (int i = 0; i < Header_Count; i++)
        {
            elf32_shdr& Section_Header = Section_Headers[i];

            string name = Names[Section_Header.sh_name];

            if (name == type)
            {
                return Section_Header.sh_offset;
            }
        }
    }
    else
    {
        elf64_shdr* Section_Headers = reinterpret_cast<elf64_shdr*>(&buffer[Current_Section_Header]);
        for (int i = 0; i < Header_Count; i++)
        {
            elf64_shdr& Section_Header = Section_Headers[i];

            string name = Names[Section_Header.sh_name];

            if (name == type)
            {
                return Section_Header.sh_offset;
            }
        }
    }
    cout << "Error: Couldn't find section " << type << endl;
}