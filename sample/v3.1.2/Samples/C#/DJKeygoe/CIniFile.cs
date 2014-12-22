using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;

namespace DJKeygoe
{
    public class ClsIniFile
    {
        [DllImport("kernel32")]
        private static extern int WritePrivateProfileString(string section,
            string key, string val, string filePath);

        [DllImport("kernel32")]
        private static extern int GetPrivateProfileString(string section,
            string key, string def, StringBuilder val, int size, string filePath);

        [DllImport("kernel32")]
        private static extern Int32 GetModuleFileName(
                                         Int32 hModule,    // handle to module
                                         StringBuilder lpFilename,  // path buffer
                                         Int32 nSize         // size of buffer
                                       );

        [DllImport("kernel32")]
        private static extern Int32 GetPrivateProfileInt(
                                         string section,  // section name
                                         string key,  // key name
                                         int iDefault,       // return value if key name not found
                                         string filePath  // initialization file name
                                       );

        protected string strIniPath;

        public ClsIniFile(string strFilePath)
        {
            strIniPath = strFilePath;
        }

        public void SetIniFileName(string strFilePath)
        {
            strIniPath = strFilePath;
        }

        public int WriteFileString(string section, string key, string val)
        {
            return WritePrivateProfileString(section, key, val, strIniPath);
        }

        public int GetFileString(string section, string key, string def, StringBuilder val, int size)
        {
            return GetPrivateProfileString(section, key, def, val, size, strIniPath);
        }

        public int GetFileInt(string section, string key, int iDeafult)
        {
            return GetPrivateProfileInt(section, key, iDeafult, strIniPath);
        }

        public int GetExeFilePath(StringBuilder lpFilePath, Int32 nSize)
        {
            return GetModuleFileName(0, lpFilePath, nSize);
        }
    };
}