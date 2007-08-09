/*=========================================================================

  Program:   CMake - Cross-Platform Makefile Generator
  Module:    $RCSfile$
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2002 Kitware, Inc., Insight Consortium.  All rights reserved.
  See Copyright.txt or http://www.cmake.org/HTML/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#include "cmDocumentation.h"

#include "cmSystemTools.h"
#include "cmVersion.h"
#include <cmsys/Directory.hxx>


const cmDocumentationEntry cmDocumentation::cmSection::EmptySection ={0,0,0};

//----------------------------------------------------------------------------
static const cmDocumentationEntry cmDocumentationStandardOptions[] =
{
  {"--copyright [file]", "Print the CMake copyright and exit.",
   "If a file is specified, the copyright is written into it."},
  {"--help", "Print usage information and exit.",
   "Usage describes the basic command line interface and its options."},
  {"--help-full [file]", "Print full help and exit.",
   "Full help displays most of the documentation provided by the UNIX "
   "man page.  It is provided for use on non-UNIX platforms, but is "
   "also convenient if the man page is not installed.  If a file is "
   "specified, the help is written into it."},
  {"--help-html [file]", "Print full help in HTML format.",
   "This option is used by CMake authors to help produce web pages.  "
   "If a file is specified, the help is written into it."},
  {"--help-man [file]", "Print full help as a UNIX man page and exit.",
   "This option is used by the cmake build to generate the UNIX man page.  "
   "If a file is specified, the help is written into it."},
  {"--version [file]", "Show program name/version banner and exit.",
   "If a file is specified, the version is written into it."},
  {0,0,0}
};

//----------------------------------------------------------------------------
static const cmDocumentationEntry cmModulesDocumentationDescription[] =
{
  {0,
  "  CMake Modules - Modules coming with CMake, the Cross-Platform Makefile "
  "Generator.", 0},
//  CMAKE_DOCUMENTATION_OVERVIEW,
  {0,
  "This is the documentation for the modules and scripts coming with CMake. "
  "Using these modules you can check the computer system for "
  "installed software packages, features of the compiler and the "
  "existance of headers to name just a few.", 0},
  {0,0,0}
};

//----------------------------------------------------------------------------
static const cmDocumentationEntry cmPropertiesDocumentationDescription[] =
{
  {0,
   "  CMake Properties - Properties supported by CMake, "
   "the Cross-Platform Makefile Generator.", 0},
//  CMAKE_DOCUMENTATION_OVERVIEW,
  {0,
   "This is the documentation for the properties supported by CMake. "
   "Properties can have different scopes. They can either be assigned to a "
   "source file, a directory, a target or globally to CMake. By modifying the "
   "values of properties the behaviour of the buildsystem can be customized.",
   0},
  {0,0,0}
};

//----------------------------------------------------------------------------
static const cmDocumentationEntry cmCompatCommandsDocumentationDescription[] =
{
  {0,
   "  CMake Compatibility Listfile Commands - "
   "Obsolete commands supported by CMake for compatibility.", 0},
//  CMAKE_DOCUMENTATION_OVERVIEW,
  {0,
  "This is the documentation for now obsolete listfile commands from previous "
  "CMake versions, which are still supported for compatibility reasons. You "
  "should instead use the newer, faster and shinier new commands. ;-)", 0},
  {0,0,0}
};

//----------------------------------------------------------------------------
static const cmDocumentationEntry cmDocumentationCommandsHeader[] =
{
  {0,
   "The following commands are available in CMakeLists.txt code:", 0},
  {0,0,0}
};

//----------------------------------------------------------------------------
static const cmDocumentationEntry cmDocumentationGlobalPropertiesHeader[] =
{
  {0,
   "The following global properties are available in CMakeLists.txt code:", 0},
  {0,0,0}
};

//----------------------------------------------------------------------------
static const cmDocumentationEntry cmDocumentationDirectoryPropertiesHeader[] =
{
  {0
   ,"The following directory properties are available in CMakeLists.txt code:"
   ,0},
  {0,0,0}
};

//----------------------------------------------------------------------------
static const cmDocumentationEntry cmDocumentationTargetPropertiesHeader[] =
{
  {0,
   "The following target properties are available in CMakeLists.txt code:", 0},
  {0,0,0}
};

//----------------------------------------------------------------------------
static const cmDocumentationEntry cmDocumentationTestPropertiesHeader[] =
{
  {0
   ,"The following properties for tests are available in CMakeLists.txt code:"
   ,0},
  {0,0,0}
};

//----------------------------------------------------------------------------
static const cmDocumentationEntry cmDocumentationSourceFilePropertiesHeader[] =
{
  {0
  ,"The following source file properties are available in CMakeLists.txt code:"
  , 0},
  {0,0,0}
};

//----------------------------------------------------------------------------
static const cmDocumentationEntry cmDocumentationVariablePropertiesHeader[] =
{
  {0, "The following variables are available in CMakeLists.txt code:", 0},
  {0,0,0}
};

//----------------------------------------------------------------------------
static const cmDocumentationEntry 
                             cmDocumentationCachedVariablePropertiesHeader[] =
{
  {0,"The following cache variables are available in CMakeLists.txt code:", 0},
  {0,0,0}
};

//----------------------------------------------------------------------------
static const cmDocumentationEntry cmDocumentationModulesHeader[] =
{
  {0,
   "The following modules are provided with CMake. "
   "They can be used with INCLUDE(ModuleName).", 0},
  {0,0,0}
};

//----------------------------------------------------------------------------
static const cmDocumentationEntry cmDocumentationGeneratorsHeader[] =
{
  {0,
   "The following generators are available on this platform:", 0},
  {0,0,0}
};

//----------------------------------------------------------------------------
static const cmDocumentationEntry cmDocumentationStandardSeeAlso[] =
{
  {0,
   "The following resources are available to get help using CMake:", 0},
  {"Home Page",
   "http://www.cmake.org",
   "The primary starting point for learning about CMake."},
  {"Frequently Asked Questions",
   "http://www.cmake.org/Wiki/CMake_FAQ",
   "A Wiki is provided containing answers to frequently asked questions. "},
  {"Online Documentation",
   "http://www.cmake.org/HTML/Documentation.html",
   "Links to available documentation may be found on this web page."},
  {"Mailing List",
   "http://www.cmake.org/HTML/MailingLists.html",
   "For help and discussion about using cmake, a mailing list is provided at "
   "cmake@cmake.org. "
   "The list is member-post-only but one may sign up on the CMake web page. "
   "Please first read the full documentation at "
   "http://www.cmake.org before posting questions to the list."},
  {0,
   "Summary of helpful links:\n"
   "  Home: http://www.cmake.org\n"
   "  Docs: http://www.cmake.org/HTML/Documentation.html\n"
   "  Mail: http://www.cmake.org/HTML/MailingLists.html\n"
   "  FAQ:  http://www.cmake.org/Wiki/CMake_FAQ\n"
   , 0},
  {0,0,0}
};

//----------------------------------------------------------------------------
const cmDocumentationEntry cmDocumentationAuthor[] =
{
  {0,
   "This manual page was generated by the \"--help-man\" option.", 0},
  {0,0,0}
};

//----------------------------------------------------------------------------
const cmDocumentationEntry cmDocumentationCopyright[] =
{
  {0,
   "Copyright (c) 2002 Kitware, Inc., Insight Consortium.  "
   "All rights reserved.", 0},
  {0,
   "Redistribution and use in source and binary forms, with or without "
   "modification, are permitted provided that the following conditions are "
   "met:", 0},
  {"",
   "Redistributions of source code must retain the above copyright notice, "
   "this list of conditions and the following disclaimer.", 0},
  {"",
   "Redistributions in binary form must reproduce the above copyright "
   "notice, this list of conditions and the following disclaimer in the "
   "documentation and/or other materials provided with the distribution.",
   0},
  {"",
   "The names of Kitware, Inc., the Insight Consortium, or the names of "
   "any consortium members, or of any contributors, may not be used to "
   "endorse or promote products derived from this software without "
   "specific prior written permission.", 0},
  {"",
   "Modified source versions must be plainly marked as such, and must "
   "not be misrepresented as being the original software.", 0},
  {0,
   "THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND CONTRIBUTORS "
   "``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT "
   "LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR "
   "A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR "
   "CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, "
   "EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, "
   "PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR "
   "PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF "
   "LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING "
   "NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS "
   "SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.", 0},
  {0, 0, 0}
};

//----------------------------------------------------------------------------
cmDocumentation::cmDocumentation()
:NameSection          ("Name",                            "NAME")
,UsageSection         ("Usage",                           "SYNOPSIS")
,DescriptionSection   ("",                                "DESCRIPTION")
,OptionsSection       ("Command-Line Options",            "OPTIONS")
,CommandsSection      ("Listfile Commands",               "COMMANDS")
,CompatCommandsSection("Compatibility Listfile Commands",
                       "COMPATIBILITY COMMANDS")
,ModulesSection       ("Standard CMake Modules",          "MODULES")
,GeneratorsSection    ("Generators",                      "GENERATORS")
,SeeAlsoSection       ("See Also",                        "SEE ALSO")
,CopyrightSection     ("Copyright",                       "COPYRIGHT")
,AuthorSection        ("Author",                          "AUTHOR")
,GlobalPropertiesSection        ("Standard Properties",   "GLOBAL PROPERTIES")
,DirectoryPropertiesSection     ("Directory Properties",  
                                 "DIRECTORY PROPERTIES")
,TargetPropertiesSection        ("Target Properties",     "TARGET PROPERTIES")
,TestPropertiesSection          ("Test Properties",       "TEST PROPERTIES")
,SourceFilePropertiesSection    ("Sourcefile Properties", 
                                 "SOURCEFILE PROPERTIES")
,VariablePropertiesSection      ("Variables",             "VARIABLES")
,CachedVariablePropertiesSection("Cached Variables",      "CACHE VARIABLES")
{
  this->CurrentForm = TextForm;
  this->TextIndent = "";
  this->TextWidth = 77;
  
  this->PropertySections[cmProperty::GLOBAL] = &this->GlobalPropertiesSection;
  this->PropertySections[cmProperty::DIRECTORY] = 
                                             &this->DirectoryPropertiesSection;
  this->PropertySections[cmProperty::TARGET] = &this->TargetPropertiesSection;
  this->PropertySections[cmProperty::TEST] = &this->TestPropertiesSection;
  this->PropertySections[cmProperty::SOURCE_FILE] = 
                                            &this->SourceFilePropertiesSection;
  this->PropertySections[cmProperty::VARIABLE] = 
                                              &this->VariablePropertiesSection;
  this->PropertySections[cmProperty::CACHED_VARIABLE] = 
                                        &this->CachedVariablePropertiesSection;
}

//----------------------------------------------------------------------------
cmDocumentation::~cmDocumentation()
{
  for(std::vector< char* >::iterator i = this->ModuleStrings.begin();
      i != this->ModuleStrings.end(); ++i)
    {
    delete [] *i;
    }
}

//----------------------------------------------------------------------------
bool cmDocumentation::PrintCopyright(std::ostream& os)
{
  for(const cmDocumentationEntry* op = cmDocumentationCopyright;
      op->brief; ++op)
    {
    if(op->name)
      {
      os << " * ";
      this->TextIndent = "    ";
      this->PrintColumn(os, op->brief);
      }
    else
      {
      this->TextIndent = "";
      this->PrintColumn(os, op->brief);
      }
    os << "\n";
    }
  return true;
}

//----------------------------------------------------------------------------
bool cmDocumentation::PrintVersion(std::ostream& os)
{
  os << this->GetNameString() << " version " 
     << cmVersion::GetCMakeVersion() << "\n";
  return true;
}

//----------------------------------------------------------------------------
void cmDocumentation::AddSection(const char* name,
                                 const cmDocumentationEntry* d)
{
  this->Names.push_back(name);
  this->Sections.push_back(d);
}

//----------------------------------------------------------------------------
void cmDocumentation::AddSection(const cmSection& section)
{
  if (!section.IsEmpty())
    {
    this->Names.push_back(section.GetName(this->CurrentForm));
    this->Sections.push_back(section.GetEntries());
    }
}

//----------------------------------------------------------------------------
void cmDocumentation::ClearSections()
{
  this->Names.erase(this->Names.begin(), this->Names.end());
  this->Sections.erase(this->Sections.begin(), this->Sections.end());
}

//----------------------------------------------------------------------------
bool cmDocumentation::PrintDocumentation(Type ht, std::ostream& os)
{
  if ((this->CurrentForm != HTMLForm) && (this->CurrentForm != ManForm))
    {
    this->PrintVersion(os);
    }

  switch (ht)
    {
    case cmDocumentation::Usage:
      return this->PrintDocumentationUsage(os);
    case cmDocumentation::Single:
      return this->PrintDocumentationSingle(os);
    case cmDocumentation::SingleModule:
      return this->PrintDocumentationSingleModule(os);
    case cmDocumentation::SingleProperty:
      return this->PrintDocumentationSingleProperty(os);
    case cmDocumentation::List:      
      return this->PrintDocumentationList(os);
    case cmDocumentation::ModuleList: 
      return this->PrintModuleList(os);
    case cmDocumentation::PropertyList: 
      return this->PrintPropertyList(os);

    case cmDocumentation::Full: 
      return this->PrintDocumentationFull(os);
    case cmDocumentation::Modules: 
      return this->PrintDocumentationModules(os);
    case cmDocumentation::Properties: 
      return this->PrintDocumentationProperties(os);
    case cmDocumentation::Commands: 
      return this->PrintDocumentationCurrentCommands(os);
    case cmDocumentation::CompatCommands: 
      return this->PrintDocumentationCompatCommands(os);

    case cmDocumentation::Copyright: 
      return this->PrintCopyright(os);
    case cmDocumentation::Version:   
      return true;
    default: return false;
    }
}

//----------------------------------------------------------------------------
bool cmDocumentation::CreateModulesSection()
{
  std::string cmakeModules = this->CMakeRoot;
  cmakeModules += "/Modules";
  cmsys::Directory dir;
  dir.Load(cmakeModules.c_str());
  if (dir.GetNumberOfFiles() > 0)
    {
    this->ModulesSection.Append(cmDocumentationModulesHeader[0]);
    for(unsigned int i = 0; i < dir.GetNumberOfFiles(); ++i)
      {
      std::string fname = dir.GetFile(i);
      if(fname.length() > 6)
        {
        if(fname.substr(fname.length()-6, 6) == ".cmake")
          {
          std::string moduleName = fname.substr(0, fname.length()-6);
          std::string path = cmakeModules;
          path += "/";
          path += fname;
          this->CreateSingleModule(path.c_str(), moduleName.c_str());
          }
        }
      } 
    cmDocumentationEntry e = { 0, 0, 0 };
    this->ModulesSection.Append(e);
    }
  return true;
}

//----------------------------------------------------------------------------
bool cmDocumentation::CreateSingleModule(const char* fname, 
                                         const char* moduleName)
{
  std::ifstream fin(fname);
  if(!fin)
    {
    std::cerr << "Internal error: can not open module." << fname << std::endl;
    return false;
    } 
  std::string line;
  std::string text;
  std::string brief;
  brief = " ";
  bool newParagraph = true;
  while ( fin && cmSystemTools::GetLineFromStream(fin, line) )
    {
    if(line.size() && line[0] == '#')
      {
      // blank line
      if(line.size() <= 2)
        {
        text += "\n"; 
        newParagraph = true;
        }
      else if(line[2] == '-') 
        {
        brief = line.c_str()+4;
        }
      else 
        {
        // two spaces
        if(line[1] == ' ' && line[2] == ' ')
          {
          if(!newParagraph)
            {
            text += "\n";
            newParagraph = true;
            }
          // Skip #, and leave space for preformatted
          text += line.c_str()+1;
          text += "\n";
          }
        else if(line[1] == ' ')
          {
          if(!newParagraph)
            {
            text += " ";
            }
          newParagraph = false;
          // skip # and space
          text += line.c_str()+2;
          }
        else
          {
          if(!newParagraph)
            {
            text += " ";
            }
          newParagraph = false;
          // skip #
          text += line.c_str()+1;
          }
        }
      }
    else
      {
      if(text.length() < 2 && brief.length() == 1)
        {
        return false;
        }
      char* pname = strcpy(new char[strlen(moduleName)+1], moduleName);
      char* ptext = strcpy(new char[text.length()+1], text.c_str());
      this->ModuleStrings.push_back(pname);
      this->ModuleStrings.push_back(ptext);
      char* pbrief = strcpy(new char[brief.length()+1], brief.c_str());
      this->ModuleStrings.push_back(pbrief);
      cmDocumentationEntry e = { pname, pbrief, ptext };
      this->ModulesSection.Append(e);
      return true;
      }
    }
  return true;
}


//----------------------------------------------------------------------------
bool cmDocumentation::PrintRequestedDocumentation(std::ostream& os)
{
  bool result = true;
  
  // Loop over requested documentation types.
  for(std::vector<RequestedHelpItem>::const_iterator 
      i = this->RequestedHelpItems.begin();
      i != this->RequestedHelpItems.end(); 
      ++i)
    {
    this->CurrentForm = i->HelpForm;
    this->CurrentArgument = i->Argument;
    // If a file name was given, use it.  Otherwise, default to the
    // given stream.
    std::ofstream* fout = 0;
    std::ostream* s = &os;
    if(i->Filename.length() > 0)
      {
      fout = new std::ofstream(i->Filename.c_str(), std::ios::out);
      if(fout)
        {
        s = fout;
        }
      else
        {
        result = false;
        }
      }
    
    // Print this documentation type to the stream.
    if(!this->PrintDocumentation(i->HelpType, *s) || !*s)
      {
      result = false;
      }
    
    // Close the file if we wrote one.
    if(fout)
      {
      delete fout;
      }
    }
  return result;
}

#define GET_OPT_ARGUMENT(target)                      \
     if((i+1 < argc) && !this->IsOption(argv[i+1]))   \
        {                                             \
        target = argv[i+1];                           \
        i = i+1;                                      \
        };


cmDocumentation::Form cmDocumentation::GetFormFromFilename(
                                                   const std::string& filename)
{
  std::string ext = cmSystemTools::GetFilenameExtension(filename);
  ext = cmSystemTools::UpperCase(ext);
  if ((ext == ".HTM") || (ext == ".HTML"))
    {
    return cmDocumentation::HTMLForm;
    }

  // ".1" to ".9" should be manpages
  if ((ext.length()==2) && (ext[1] >='1') && (ext[1]<='9'))
    {
    return cmDocumentation::ManForm;
    }

  return cmDocumentation::TextForm;
}

//----------------------------------------------------------------------------
bool cmDocumentation::CheckOptions(int argc, const char* const* argv)
{
  // Providing zero arguments gives usage information.
  if(argc == 1)
    {
    RequestedHelpItem help;
    help.HelpType = cmDocumentation::Usage;
    help.HelpForm = cmDocumentation::UsageForm;
    this->RequestedHelpItems.push_back(help);
    return true;
    }

  // Search for supported help options.

  bool result = false;
  for(int i=1; i < argc; ++i)
    {
    RequestedHelpItem help;
    // Check if this is a supported help option.
    if((strcmp(argv[i], "-help") == 0) ||
       (strcmp(argv[i], "--help") == 0) ||
       (strcmp(argv[i], "/?") == 0) ||
       (strcmp(argv[i], "-usage") == 0) ||
       (strcmp(argv[i], "-h") == 0) ||
       (strcmp(argv[i], "-H") == 0))
      {
      help.HelpType = cmDocumentation::Usage;
      help.HelpForm = cmDocumentation::UsageForm;
      GET_OPT_ARGUMENT(help.Argument);
      help.Argument = cmSystemTools::UpperCase(help.Argument);
      // special case for single command
      if (!help.Argument.empty())
        {
        help.HelpType = cmDocumentation::Single;
        }
      }
    else if(strcmp(argv[i], "--help-properties") == 0)
      {
      help.HelpType = cmDocumentation::Properties;
      GET_OPT_ARGUMENT(help.Filename);
      help.HelpForm = this->GetFormFromFilename(help.Filename);
      }
    else if(strcmp(argv[i], "--help-modules") == 0)
      {
      help.HelpType = cmDocumentation::Modules;
      GET_OPT_ARGUMENT(help.Filename);
      help.HelpForm = this->GetFormFromFilename(help.Filename);
      }
    else if(strcmp(argv[i], "--help-commands") == 0)
      {
      help.HelpType = cmDocumentation::Commands;
      GET_OPT_ARGUMENT(help.Filename);
      help.HelpForm = this->GetFormFromFilename(help.Filename);
      }
    else if(strcmp(argv[i], "--help-compatcommands") == 0)
      {
      help.HelpType = cmDocumentation::CompatCommands;
      GET_OPT_ARGUMENT(help.Filename);
      help.HelpForm = this->GetFormFromFilename(help.Filename);
      }
    else if(strcmp(argv[i], "--help-full") == 0)
      {
      help.HelpType = cmDocumentation::Full;
      GET_OPT_ARGUMENT(help.Filename);
      help.HelpForm = this->GetFormFromFilename(help.Filename);
      }
    else if(strcmp(argv[i], "--help-html") == 0)
      {
      help.HelpType = cmDocumentation::Full;
      GET_OPT_ARGUMENT(help.Filename);
      help.HelpForm = cmDocumentation::HTMLForm;
      }
    else if(strcmp(argv[i], "--help-man") == 0)
      {
      help.HelpType = cmDocumentation::Full;
      GET_OPT_ARGUMENT(help.Filename);
      help.HelpForm = cmDocumentation::ManForm;
      }
    else if(strcmp(argv[i], "--help-command") == 0)
      {
      help.HelpType = cmDocumentation::Single;
      GET_OPT_ARGUMENT(help.Argument);
      GET_OPT_ARGUMENT(help.Filename);
      help.Argument = cmSystemTools::UpperCase(help.Argument);
      help.HelpForm = this->GetFormFromFilename(help.Filename);
      }
    else if(strcmp(argv[i], "--help-module") == 0)
      {
      help.HelpType = cmDocumentation::SingleModule;
      GET_OPT_ARGUMENT(help.Argument);
      GET_OPT_ARGUMENT(help.Filename);
      help.HelpForm = this->GetFormFromFilename(help.Filename);
      }
    else if(strcmp(argv[i], "--help-property") == 0)
      {
      help.HelpType = cmDocumentation::SingleProperty;
      GET_OPT_ARGUMENT(help.Argument);
      GET_OPT_ARGUMENT(help.Filename);
      help.HelpForm = this->GetFormFromFilename(help.Filename);
      }
    else if(strcmp(argv[i], "--help-command-list") == 0)
      {
      help.HelpType = cmDocumentation::List;
      GET_OPT_ARGUMENT(help.Filename);
      help.HelpForm = cmDocumentation::TextForm;
      }
    else if(strcmp(argv[i], "--help-module-list") == 0)
      {
      help.HelpType = cmDocumentation::ModuleList;
      GET_OPT_ARGUMENT(help.Filename);
      help.HelpForm = cmDocumentation::TextForm;
      }
    else if(strcmp(argv[i], "--help-property-list") == 0)
      {
      help.HelpType = cmDocumentation::PropertyList;
      GET_OPT_ARGUMENT(help.Filename);
      help.HelpForm = cmDocumentation::TextForm;
      }
    else if(strcmp(argv[i], "--copyright") == 0)
      {
      help.HelpType = cmDocumentation::Copyright;
      GET_OPT_ARGUMENT(help.Filename);
      help.HelpForm = cmDocumentation::UsageForm;
      }
    else if((strcmp(argv[i], "--version") == 0) || 
            (strcmp(argv[i], "-version") == 0) || 
            (strcmp(argv[i], "/V") == 0))
      {
      help.HelpType = cmDocumentation::Version;
      GET_OPT_ARGUMENT(help.Filename);
      help.HelpForm = cmDocumentation::UsageForm;
      }
    if(help.HelpType != None)
      {
      // This is a help option.  See if there is a file name given.
      result = true;
      this->RequestedHelpItems.push_back(help);
      }
    }
  return result;
}

//----------------------------------------------------------------------------
void cmDocumentation::Print(Form f, std::ostream& os)
{
  this->CurrentForm = f;
  Print(os);
}

//----------------------------------------------------------------------------
void cmDocumentation::Print(std::ostream& os)
{
  for(unsigned int i=0; i < this->Sections.size(); ++i)
    {
    this->PrintSection(os, this->Sections[i], this->Names[i]);
    }
}

//----------------------------------------------------------------------------
void cmDocumentation::SetName(const char* name)
{
  this->NameString = name?name:"";
}

//----------------------------------------------------------------------------
void cmDocumentation::SetNameSection(const cmDocumentationEntry* section)
{
  this->NameSection.Set(0, section, 0);
}

//----------------------------------------------------------------------------
void cmDocumentation::SetUsageSection(const cmDocumentationEntry* section)
{
  this->UsageSection.Set(0, section, 0);
}

//----------------------------------------------------------------------------
void cmDocumentation
::SetDescriptionSection(const cmDocumentationEntry* section)
{
  this->DescriptionSection.Set(0, section, 0);
}

//----------------------------------------------------------------------------
void cmDocumentation::SetOptionsSection(const cmDocumentationEntry* section)
{
  this->OptionsSection.Set(0, section, cmDocumentationStandardOptions);
}

//----------------------------------------------------------------------------
void cmDocumentation::SetCommandsSection(const cmDocumentationEntry* section)
{
  this->CommandsSection.Set(cmDocumentationCommandsHeader, section, 0);
}

//----------------------------------------------------------------------------
void cmDocumentation::SetCompatCommandsSection(const cmDocumentationEntry* 
                                               section)
{
  this->CompatCommandsSection.Set(cmDocumentationCommandsHeader, section, 0);
}

//----------------------------------------------------------------------------
void cmDocumentation
::SetPropertiesSection(const cmDocumentationEntry* section, 
                       cmProperty::ScopeType type)
{
  switch(type)
  {
  case cmProperty::GLOBAL:
    this->GlobalPropertiesSection.Set(
                            cmDocumentationGlobalPropertiesHeader, section, 0);
    break;
  case cmProperty::DIRECTORY:
    this->DirectoryPropertiesSection.Set(
                         cmDocumentationDirectoryPropertiesHeader, section, 0);
    break;
  case cmProperty::TARGET:
    this->TargetPropertiesSection.Set(
                            cmDocumentationTargetPropertiesHeader, section, 0);
    break;
  case cmProperty::TEST:
    this->TestPropertiesSection.Set(
                              cmDocumentationTestPropertiesHeader, section, 0);
    break;
  case cmProperty::SOURCE_FILE:
    this->SourceFilePropertiesSection.Set(
                        cmDocumentationSourceFilePropertiesHeader, section, 0);
    break;
  case cmProperty::VARIABLE:
    this->VariablePropertiesSection.Set(
                        cmDocumentationVariablePropertiesHeader, section, 0);
    break;
  case cmProperty::CACHED_VARIABLE:
    this->CachedVariablePropertiesSection.Set(
                    cmDocumentationCachedVariablePropertiesHeader, section, 0);
    break;
  default:
    break;
  }
}

//----------------------------------------------------------------------------
void cmDocumentation
::SetGeneratorsSection(const cmDocumentationEntry* section)
{
  this->GeneratorsSection.Set(cmDocumentationGeneratorsHeader, section, 0);
}

//----------------------------------------------------------------------------
void cmDocumentation::SetSeeAlsoList(const cmDocumentationEntry* also)
{
  this->SeeAlsoSection.Clear();
  this->SeeAlsoString = ".B ";
  for(const cmDocumentationEntry* i = also; i->brief; ++i)
    {
    this->SeeAlsoString += i->brief;
    this->SeeAlsoString += (i+1)->brief? "(1), ":"(1)";    
    }
  cmDocumentationEntry e = {0, 0, 0};
  e.brief = this->SeeAlsoString.c_str();
  this->SeeAlsoSection.Append(e);
  for(const cmDocumentationEntry* i = cmDocumentationStandardSeeAlso;
      i->brief; ++i)
    {
    this->SeeAlsoSection.Append(*i);
    }
  e.brief = 0;
  this->SeeAlsoSection.Append(e);
}

//----------------------------------------------------------------------------
void cmDocumentation::PrintSection(std::ostream& os,
                                   const cmDocumentationEntry* section,
                                   const char* name)
{
  switch (this->CurrentForm)
    {
    case TextForm: this->PrintSectionText(os, section, name); break;
    case HTMLForm: this->PrintSectionHTML(os, section, name); break;
    case ManForm: this->PrintSectionMan(os, section, name); break;
    case UsageForm: this->PrintSectionUsage(os, section, name); break;
    }
}

//----------------------------------------------------------------------------
void cmDocumentation::PrintSectionText(std::ostream& os,
                                       const cmDocumentationEntry* section,
                                       const char* name)
{
  if(name)
    {
    os <<
      "---------------------------------------"
      "---------------------------------------\n";
    os << name << "\n\n";
    }
  if(!section) { return; }
  for(const cmDocumentationEntry* op = section; op->brief; ++op)
    {
    if(op->name)
      {
      if(op->name[0])
        {
        os << "  " << op->name << "\n";
        }
      this->TextIndent = "       ";
      this->PrintFormatted(os, op->brief);
      if(op->full)
        {
        os << "\n";
        this->PrintFormatted(os, op->full);
        }
      }
    else
      {
      this->TextIndent = "";
      this->PrintFormatted(os, op->brief);
      }
    os << "\n";
    }  
}

//----------------------------------------------------------------------------
void cmDocumentation::PrintSectionHTML(std::ostream& os,
                                       const cmDocumentationEntry* section,
                                       const char* name)
{
  if(name)
    {
    os << "<h2>" << name << "</h2>\n";
    }
  if(!section) { return; }
  for(const cmDocumentationEntry* op = section; op->brief;)
    {
    if(op->name)
      {
      os << "<ul>\n";
      for(;op->name;++op)
        {
        os << "  <li>\n";
        if(op->name[0])
          {
          os << "    <b><code>";
          this->PrintHTMLEscapes(os, op->name);
          os << "</code></b>: ";
          }
        this->PrintHTMLEscapes(os, op->brief);
        if(op->full)
          {
          os << "<br>\n    ";
          this->PrintFormatted(os, op->full);
          }
        os << "\n";
        os << "  </li>\n";
        }
      os << "</ul>\n";
      }
    else
      {
      this->PrintFormatted(os, op->brief);
      os << "\n";
      ++op;
      }
    }
}

//----------------------------------------------------------------------------
void cmDocumentation::PrintSectionMan(std::ostream& os,
                                      const cmDocumentationEntry* section,
                                      const char* name)
{
  if(name)
    {
    os << ".SH " << name << "\n";
    }
  if(!section) { return; }
  for(const cmDocumentationEntry* op = section; op->brief; ++op)
    {
    if(op->name)
      {
      os << ".TP\n"
         << ".B " << (op->name[0]?op->name:"*") << "\n";
      this->PrintFormatted(os, op->brief);
      this->PrintFormatted(os, op->full);
      }
    else
      {
      os << ".PP\n";
      this->PrintFormatted(os, op->brief);
      }
    }  
}

//----------------------------------------------------------------------------
void cmDocumentation::PrintSectionUsage(std::ostream& os,
                                        const cmDocumentationEntry* section,
                                        const char* name)
{
  if(name)
    {
    os << name << "\n";
    }
  if(!section) { return; }
  for(const cmDocumentationEntry* op = section; op->brief; ++op)
    {
    if(op->name)
      {
      os << "  " << op->name;
      this->TextIndent = "                                ";
      int align = static_cast<int>(strlen(this->TextIndent))-4;
      for(int i = static_cast<int>(strlen(op->name)); i < align; ++i)
        {
        os << " ";
        }
      if ( strlen(op->name) > strlen(this->TextIndent)-4 )
        {
        os << "\n";
        os.write(this->TextIndent, strlen(this->TextIndent)-2);
        }
      os << "= ";
      this->PrintColumn(os, op->brief);
      os << "\n";
      }
    else
      {
      os << "\n";
      this->TextIndent = "";
      this->PrintFormatted(os, op->brief);
      }
    }
  os << "\n";
}

//----------------------------------------------------------------------------
void cmDocumentation::PrintFormatted(std::ostream& os, const char* text)
{
  if(!text)
    {
    return;
    }
  const char* ptr = text;
  while(*ptr)
    {
    // Any ptrs starting in a space are treated as preformatted text.
    std::string preformatted;
    while(*ptr == ' ')
      {
      for(char ch = *ptr; ch && ch != '\n'; ++ptr, ch = *ptr)
        {
        preformatted.append(1, ch);
        }
      if(*ptr)
        {
        ++ptr;
        preformatted.append(1, '\n');
        }
      }
    if(preformatted.length())
      {
      this->PrintPreformatted(os, preformatted.c_str());
      }
    
    // Other ptrs are treated as paragraphs.
    std::string paragraph;
    for(char ch = *ptr; ch && ch != '\n'; ++ptr, ch = *ptr)
      {
      paragraph.append(1, ch);
      }
    if(*ptr)
      {
      ++ptr;
      paragraph.append(1, '\n');
      }
    if(paragraph.length())
      {
      this->PrintParagraph(os, paragraph.c_str());
      }
    }
}

//----------------------------------------------------------------------------
void cmDocumentation::PrintPreformatted(std::ostream& os, const char* text)
{
  switch (this->CurrentForm)
    {
    case TextForm: this->PrintPreformattedText(os, text); break;
    case HTMLForm: this->PrintPreformattedHTML(os, text); break;
    case ManForm: this->PrintPreformattedMan(os, text); break;
    case UsageForm: this->PrintPreformattedText(os, text); break;
    }
}

//----------------------------------------------------------------------------
void cmDocumentation::PrintParagraph(std::ostream& os, const char* text)
{
  switch (this->CurrentForm)
    {
    case TextForm: this->PrintParagraphText(os, text); break;
    case HTMLForm: this->PrintParagraphHTML(os, text); break;
    case ManForm: this->PrintParagraphMan(os, text); break;
    case UsageForm: this->PrintParagraphText(os, text); break;
    }
}

//----------------------------------------------------------------------------
void cmDocumentation
::PrintPreformattedText(std::ostream& os, const char* text)
{
  bool newline = true;
  for(const char* ptr = text; *ptr; ++ptr)
    {
    if(newline)
      {
      os << this->TextIndent;
      newline = false;
      }
    os << *ptr;
    if(*ptr == '\n')
      {
      newline = true;
      }
    }
  os << "\n";
}

//----------------------------------------------------------------------------
void cmDocumentation::PrintParagraphText(std::ostream& os, const char* text)
{
  os << this->TextIndent;
  this->PrintColumn(os, text);
  os << "\n";
}

//----------------------------------------------------------------------------
void cmDocumentation
::PrintPreformattedHTML(std::ostream& os, const char* text)
{
  os << "<pre>";
  this->PrintHTMLEscapes(os, text);
  os << "</pre>\n    ";
}

//----------------------------------------------------------------------------
void cmDocumentation::PrintParagraphHTML(std::ostream& os, const char* text)
{
  os << "<p>";
  this->PrintHTMLEscapes(os, text);
}

//----------------------------------------------------------------------------
void cmDocumentation::PrintPreformattedMan(std::ostream& os, const char* text)
{
  std::string man_text = text;
  cmSystemTools::ReplaceString(man_text, "\\", "\\\\");
  os << man_text << "\n";
}

//----------------------------------------------------------------------------
void cmDocumentation::PrintParagraphMan(std::ostream& os, const char* text)
{
  std::string man_text = text;
  cmSystemTools::ReplaceString(man_text, "\\", "\\\\");
  os << man_text << "\n\n";
}

//----------------------------------------------------------------------------
void cmDocumentation::PrintColumn(std::ostream& os, const char* text)
{
  // Print text arranged in an indented column of fixed witdh.
  const char* l = text;
  int column = 0;
  bool newSentence = false;
  bool firstLine = true;
  int width = this->TextWidth - static_cast<int>(strlen(this->TextIndent));
  
  // Loop until the end of the text.
  while(*l)
    {
    // Parse the next word.
    const char* r = l;
    while(*r && (*r != '\n') && (*r != ' ')) { ++r; }
    
    // Does it fit on this line?
    if(r-l < (width-column-(newSentence?1:0)))
      {
      // Word fits on this line.
      if(r > l)
        {
        if(column)
          {
          // Not first word on line.  Separate from the previous word
          // by a space, or two if this is a new sentence.
          if(newSentence)
            {
            os << "  ";
            column += 2;
            }
          else
            {
            os << " ";
            column += 1;
            }
          }
        else
          {
          // First word on line.  Print indentation unless this is the
          // first line.
          os << (firstLine?"":this->TextIndent);
          }
        
        // Print the word.
        os.write(l, static_cast<long>(r-l));
        newSentence = (*(r-1) == '.');
        }
      
      if(*r == '\n')
        {
        // Text provided a newline.  Start a new line.
        os << "\n";
        ++r;
        column = 0;
        firstLine = false;
        }
      else
        {
        // No provided newline.  Continue this line.
        column += static_cast<long>(r-l);
        }
      }
    else
      {
      // Word does not fit on this line.  Start a new line.
      os << "\n";
      firstLine = false;
      if(r > l)
        {
        os << this->TextIndent;
        os.write(l, static_cast<long>(r-l));
        column = static_cast<long>(r-l);
        newSentence = (*(r-1) == '.');
        }
      else
        {
        column = 0;
        }
      }
    
    // Move to beginning of next word.  Skip over whitespace.
    l = r;
    while(*l && (*l == ' ')) { ++l; }    
    }
}

//----------------------------------------------------------------------------
static bool cmDocumentationIsHyperlinkChar(char c)
{
  // This is not a complete list but works for CMake documentation.
  return ((c >= 'A' && c <= 'Z') ||
          (c >= 'a' && c <= 'z') ||
          (c >= '0' && c <= '9') ||
          c == '-' || c == '.' || c == '/' || c == '~' || c == '@' ||
          c == ':' || c == '_' || c == '&' || c == '?' || c == '=');
}

//----------------------------------------------------------------------------
static void cmDocumentationPrintHTMLChar(std::ostream& os, char c)
{
  // Use an escape sequence if necessary.
  static cmDocumentationEntry escapes[] =
  {
    {"<", "&lt;", 0},
    {">", "&gt;", 0},
    {"&", "&amp;", 0},
    {"\n", "<br>", 0},
    {0,0,0}
  };
  for(const cmDocumentationEntry* op = escapes; op->name; ++op)
    {
    if(op->name[0] == c)
      {
      os << op->brief;
      return;
      }
    }

  // No escape sequence is needed.
  os << c;
}

//----------------------------------------------------------------------------
const char* cmDocumentationPrintHTMLLink(std::ostream& os, const char* begin)
{
  // Look for the end of the link.
  const char* end = begin;
  while(cmDocumentationIsHyperlinkChar(*end))
    {
    ++end;
    }

  // Print the hyperlink itself.
  os << "<a href=\"";
  for(const char* c = begin; c != end; ++c)
    {
    cmDocumentationPrintHTMLChar(os, *c);
    }
  os << "\">";

  // The name of the hyperlink is the text itself.
  for(const char* c = begin; c != end; ++c)
    {
    cmDocumentationPrintHTMLChar(os, *c);
    }
  os << "</a>";

  // Return the position at which to continue scanning the input
  // string.
  return end;
}

//----------------------------------------------------------------------------
void cmDocumentation::PrintHTMLEscapes(std::ostream& os, const char* text)
{
  // Hyperlink prefixes.
  static const char* hyperlinks[] = {"http://", "ftp://", "mailto:", 0};

  // Print each character.
  for(const char* p = text; *p;)
    {
    // Handle hyperlinks specially to make them active.
    bool found_hyperlink = false;
    for(const char** h = hyperlinks; !found_hyperlink && *h; ++h)
      {
      if(strncmp(p, *h, strlen(*h)) == 0)
        {
        p = cmDocumentationPrintHTMLLink(os, p);
        found_hyperlink = true;
        }
      }

    // Print other characters normally.
    if(!found_hyperlink)
      {
      cmDocumentationPrintHTMLChar(os, *p++);
      }
    }
}

//----------------------------------------------------------------------------
bool cmDocumentation::PrintDocumentationSingle(std::ostream& os)
{
  if(this->CommandsSection.IsEmpty())
    {
    os << "Internal error: commands list is empty." << std::endl;
    return false;
    }
  if(this->CurrentArgument.length() == 0)
    {
    os << "Argument --help-command needs a command name.\n";
    return false;
    }
  for(const cmDocumentationEntry* entry = this->CommandsSection.GetEntries();
      entry->brief; ++entry)
    {
    if(entry->name && this->CurrentArgument == entry->name)
      {
      this->PrintDocumentationCommand(os, entry);
      return true;
      }
    }
  for(const cmDocumentationEntry* 
      entry = this->CompatCommandsSection.GetEntries();
      entry->brief; 
      ++entry)
    {
    if(entry->name && this->CurrentArgument == entry->name)
      {
      this->PrintDocumentationCommand(os, entry);
      return true;
      }
    }

  // Argument was not a command.  Complain.
  os << "Argument \"" << this->CurrentArgument.c_str()
     << "\" to --help-command is not a CMake command.  "
     << "Use --help-command-list to see all commands.\n";
  return false;
}

//----------------------------------------------------------------------------
bool cmDocumentation::PrintDocumentationSingleModule(std::ostream& os)
{
  if(this->CurrentArgument.length() == 0)
    {
    os << "Argument --help-module needs a module name.\n";
    return false;
    }
  std::string cmakeModules = this->CMakeRoot;
  cmakeModules += "/Modules/";
  cmakeModules += this->CurrentArgument;
  cmakeModules += ".cmake";
  if(cmSystemTools::FileExists(cmakeModules.c_str())
     && this->CreateSingleModule(cmakeModules.c_str(), 
                                 this->CurrentArgument.c_str()))
    {
    this->PrintDocumentationCommand(os, this->ModulesSection.GetEntries());
    os <<  "\n       Defined in: ";
    os << cmakeModules << "\n";
    return true;
    }
  // Argument was not a module.  Complain.
  os << "Argument \"" << this->CurrentArgument.c_str()
     << "\" to --help-module is not a CMake module.";
  return false;
}

//----------------------------------------------------------------------------
bool cmDocumentation::PrintDocumentationSingleProperty(std::ostream& os)
{
  if(this->GlobalPropertiesSection.IsEmpty())
    {
    os << "Internal error: properties list is empty." << std::endl;
    return false;
    }
  if(this->CurrentArgument.length() == 0)
    {
    os << "Argument --help-property needs a property name.\n";
    return false;
    }

  for(std::map<cmProperty::ScopeType, cmSection*>::const_iterator 
      sectionIt = this->PropertySections.begin();
      sectionIt != this->PropertySections.end();
      ++sectionIt)
    {
    for(const cmDocumentationEntry* 
        entry = sectionIt->second->GetEntries(); entry->brief; ++entry)
      {
      if(entry->name && this->CurrentArgument == entry->name)
        {
        this->PrintDocumentationCommand(os, entry);
        return true;
        }
      }
    }
  // Argument was not a command.  Complain.
  os << "Argument \"" << this->CurrentArgument.c_str()
     << "\" to --help-property is not a CMake property.  "
     << "Use --help-property-list to see all properties.\n";
  return false;
}

//----------------------------------------------------------------------------
bool cmDocumentation::PrintDocumentationList(std::ostream& os)
{
  if(this->CommandsSection.IsEmpty())
    {
    os << "Internal error: commands list is empty." << std::endl;
    return false;
    }
  for(const cmDocumentationEntry* entry = this->CommandsSection.GetEntries();
      entry->brief; ++entry)
    {
    if(entry->name)
      {
      os << entry->name << std::endl;
      }
    }
  os << "\nCompatibility commands:" << std::endl;
  for(const cmDocumentationEntry* 
      entry = this->CompatCommandsSection.GetEntries();
      entry->brief; 
      ++entry)
    {
    if(entry->name)
      {
      os << entry->name << std::endl;
      }
    }
  return true;
}

//----------------------------------------------------------------------------
bool cmDocumentation::PrintPropertyList(std::ostream& os)
{
  if(this->GlobalPropertiesSection.IsEmpty())
    {
    os << "Internal error: properties list is empty." << std::endl;
    return false;
    }
  for(const cmDocumentationEntry* 
      entry = this->GlobalPropertiesSection.GetEntries();
      entry->brief; 
      ++entry)
    {
    if(entry->name)
      {
      os << entry->name << std::endl;
      }
    }

  for(std::map<cmProperty::ScopeType, cmSection*>::const_iterator 
      sectionIt = this->PropertySections.begin();
      sectionIt != this->PropertySections.end();
      ++sectionIt)
    {
    for(const cmDocumentationEntry* 
        entry = sectionIt->second->GetEntries(); entry->brief; ++entry)
      {
      if(entry->name)
        {
        os << entry->name << std::endl;
        }
      }
    }

  return true;
}

//----------------------------------------------------------------------------
bool cmDocumentation::PrintModuleList(std::ostream& os)
{
  this->CreateModulesSection();
  if(this->ModulesSection.IsEmpty())
    {
    os << "Internal error: modules list is empty." << std::endl;
    return false;
    }
  for(const cmDocumentationEntry* entry = this->ModulesSection.GetEntries();
      entry->brief; ++entry)
    {
    if(entry->name)
      {
      os << entry->name << std::endl;
      }
    }
  return true;
}

//----------------------------------------------------------------------------
bool cmDocumentation::PrintDocumentationUsage(std::ostream& os)
{
  this->CreateUsageDocumentation();
  this->Print(os);
  return true;
}

//----------------------------------------------------------------------------
bool cmDocumentation::PrintDocumentationFull(std::ostream& os)
{
  this->CreateFullDocumentation();
  this->PrintHeader(GetNameString(), os);
  this->Print(os);
  this->PrintFooter(os);
  return true;
}

//----------------------------------------------------------------------------
bool cmDocumentation::PrintDocumentationModules(std::ostream& os)
{
  this->CreateModulesDocumentation();
  this->PrintHeader(GetNameString(), os);
  this->Print(os);
  this->PrintFooter(os);
  return true;
}

//----------------------------------------------------------------------------
bool cmDocumentation::PrintDocumentationProperties(std::ostream& os)
{
  this->CreatePropertiesDocumentation();
  this->PrintHeader(GetNameString(), os);
  this->Print(os);
  this->PrintFooter(os);
  return true;
}

//----------------------------------------------------------------------------
bool cmDocumentation::PrintDocumentationCurrentCommands(std::ostream& os)
{
  this->CreateCurrentCommandsDocumentation();
  this->PrintHeader(GetNameString(), os);
  this->Print(os);
  this->PrintFooter(os);
  return true;
}

//----------------------------------------------------------------------------
bool cmDocumentation::PrintDocumentationCompatCommands(std::ostream& os)
{
  this->CreateCompatCommandsDocumentation();
  this->PrintHeader(GetNameString(), os);
  this->Print(os);
  this->PrintFooter(os);
  return true;
}

//----------------------------------------------------------------------------
void cmDocumentation::PrintHeader(const char* name, std::ostream& os)
{
  switch(this->CurrentForm)
    {
    case HTMLForm:
  os << "<html><body>\n";
       break;
    case ManForm:
       os << ".TH " << name << " 1 \""
     << cmSystemTools::GetCurrentDateTime("%B %d, %Y").c_str()
     << "\" \"" << this->GetNameString() 
     << " " << cmVersion::GetCMakeVersion()
     << "\"\n";
       break;
    case TextForm:
    case UsageForm:
       break;
    }
}

//----------------------------------------------------------------------------
void cmDocumentation::PrintFooter(std::ostream& os)
{
  switch(this->CurrentForm)
    {
    case HTMLForm:
       os << "</body></html>\n";
       break;
    case ManForm:
    case TextForm:
    case UsageForm:
       break;
    }
}

//----------------------------------------------------------------------------
void cmDocumentation::PrintDocumentationCommand(std::ostream& os,
                                             const cmDocumentationEntry* entry)
{
  cmDocumentationEntry singleCommandSection[3] =
    {
      {entry->name, entry->brief, entry->full},
      {0,0,0}
    };
  this->ClearSections();
  this->AddSection(0, &singleCommandSection[0]);
  this->Print(os);
}

//----------------------------------------------------------------------------
void cmDocumentation::CreateUsageDocumentation()
{
  this->ClearSections();
  this->AddSection(this->UsageSection);
  this->AddSection(this->OptionsSection);
  this->AddSection(this->GeneratorsSection);
}

//----------------------------------------------------------------------------
void cmDocumentation::CreateFullDocumentation()
{
  this->ClearSections();
  this->CreateModulesSection();
  this->AddSection(this->NameSection);
  this->AddSection(this->UsageSection);
  this->AddSection(this->DescriptionSection);
  this->AddSection(this->OptionsSection);
  this->AddSection(this->GeneratorsSection);
  this->AddSection(this->CommandsSection);
  this->AddSection(this->CompatCommandsSection);
  this->AddSection(this->ModulesSection);
  this->AddSection(this->GlobalPropertiesSection);
  this->AddSection(this->DirectoryPropertiesSection);
  this->AddSection(this->TargetPropertiesSection);
  this->AddSection(this->TestPropertiesSection);
  this->AddSection(this->SourceFilePropertiesSection);
  this->AddSection(this->VariablePropertiesSection);
  this->AddSection(this->CachedVariablePropertiesSection);
  
  this->AddSection(this->CopyrightSection.GetName(this->CurrentForm),
                   cmDocumentationCopyright);

  if(this->CurrentForm == ManForm)
    {
    this->AddSection(this->SeeAlsoSection);
    this->AddSection(this->AuthorSection.GetName(ManForm),
                     cmDocumentationAuthor);
    }
  else
    {
    this->AddSection(this->SeeAlsoSection.GetName(TextForm),
                     cmDocumentationStandardSeeAlso);
    }
}

void cmDocumentation::CreateCurrentCommandsDocumentation()
{
  this->ClearSections();
  this->AddSection(this->CommandsSection);
  this->AddSection(this->CopyrightSection.GetName(CurrentForm), 
                   cmDocumentationCopyright);
  this->AddSection(this->SeeAlsoSection.GetName(CurrentForm), 
                   cmDocumentationStandardSeeAlso);
}

void cmDocumentation::CreateCompatCommandsDocumentation()
{
  this->ClearSections();
  this->AddSection(this->DescriptionSection.GetName(CurrentForm), 
                   cmCompatCommandsDocumentationDescription);
  this->AddSection(this->CompatCommandsSection);
  this->AddSection(this->CopyrightSection.GetName(CurrentForm), 
                   cmDocumentationCopyright);
  this->AddSection(this->SeeAlsoSection.GetName(CurrentForm), 
                   cmDocumentationStandardSeeAlso);
}

//----------------------------------------------------------------------------
void cmDocumentation::CreateModulesDocumentation()
{
  this->ClearSections();
  this->CreateModulesSection();
  this->AddSection(this->DescriptionSection.GetName(CurrentForm), 
                   cmModulesDocumentationDescription);
  this->AddSection(this->ModulesSection);
  this->AddSection(this->CopyrightSection.GetName(CurrentForm), 
                   cmDocumentationCopyright);
  this->AddSection(this->SeeAlsoSection.GetName(CurrentForm), 
                   cmDocumentationStandardSeeAlso);
}

//----------------------------------------------------------------------------
void cmDocumentation::CreatePropertiesDocumentation()
{
  this->ClearSections();
  this->AddSection(this->DescriptionSection.GetName(CurrentForm), 
                   cmPropertiesDocumentationDescription);
  this->AddSection(this->GlobalPropertiesSection);
  this->AddSection(this->DirectoryPropertiesSection);
  this->AddSection(this->TargetPropertiesSection);
  this->AddSection(this->TestPropertiesSection);
  this->AddSection(this->SourceFilePropertiesSection);
  this->AddSection(this->VariablePropertiesSection);
  this->AddSection(this->CachedVariablePropertiesSection);
  this->AddSection(this->CopyrightSection.GetName(CurrentForm), 
                   cmDocumentationCopyright);
  this->AddSection(this->SeeAlsoSection.GetName(CurrentForm), 
                   cmDocumentationStandardSeeAlso);
}

//----------------------------------------------------------------------------
void cmDocumentation::cmSection::Set(const cmDocumentationEntry* header,
                                     const cmDocumentationEntry* section,
                                     const cmDocumentationEntry* footer)
{
  this->Entries.erase(this->Entries.begin(), this->Entries.end());
  if(header)
    {
    for(const cmDocumentationEntry* op = header; op->brief; ++op)
      {
      this->Entries.push_back(*op);
      }
    }
  if(section)
    {
    for(const cmDocumentationEntry* op = section; op->brief; ++op)
      {
      this->Entries.push_back(*op);
      }
    }
  if(footer)
    {
    for(const cmDocumentationEntry* op = footer; op->brief; ++op)
      {
      this->Entries.push_back(*op);
      }
    }
  cmDocumentationEntry empty = {0,0,0};
  this->Entries.push_back(empty);
}

//----------------------------------------------------------------------------
const char* cmDocumentation::GetNameString() const
{
  if(this->NameString.length() > 0)
    {
    return this->NameString.c_str();
    }
  else
    {
    return "CMake";
    }
}

//----------------------------------------------------------------------------
bool cmDocumentation::IsOption(const char* arg) const
{
  return ((arg[0] == '-') || (strcmp(arg, "/V") == 0) || 
          (strcmp(arg, "/?") == 0));
}
