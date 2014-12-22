package DJKeygoe;

import java.io.BufferedReader;   
import java.io.BufferedWriter;   
import java.io.FileReader;   
import java.io.FileWriter;   
import java.io.IOException;   
import java.util.regex.Matcher;   
import java.util.regex.Pattern;

public class JIniFile   
{   
    private static String RN = "\r\n";   
  
    /**  
     * 从ini配置文档中读取变量的值  
     *   
     * @param file  
     *            配置文档的路径  
     * @param section  
     *            要获取的变量所在段名称  
     * @param variable  
     *            要获取的变量名称  
     * @param defaultValue  
     *            变量名称不存在时的默认值  
     * @return 变量的值  
     * @throws IOException  
     *             抛出文档操作可能出现的io异常  
     */  
    public static String getProfileString(String file, String section, String variable, String defaultValue)   
            throws IOException   
    {   
        String strLine, valueString = "";   
        BufferedReader bufferedReader = new BufferedReader(new FileReader(file));   
        boolean isInSection = false;   
        try  
        {   
            while ((strLine = bufferedReader.readLine()) != null)   
            {   
                // 读取INI文件到内存   
  
                strLine = strLine.trim();   
                Pattern p;   
                Matcher m, m2;   
                p = Pattern.compile("\\[\\s*" + section + "\\s*\\]");   
                Pattern p2 = Pattern.compile("\\[.*\\]");   
                m = p.matcher((strLine));   
                m2 = p2.matcher((strLine));   
                if (m2.find())   
                {   
                    if (m.find())   
                    {   
                        isInSection = true;   
                    } else  
                    {   
                        isInSection = false;   
                    }   
                }   
                if (isInSection == true)   
                {   
                    strLine = strLine.trim();   
                    String[] strArray = strLine.split("=");   
                    if (strArray.length == 2)   
                    {   
                        valueString = strArray[0].trim();   
                        if (valueString.equalsIgnoreCase(variable))   
                        {   
                            valueString = strLine.substring(strLine.indexOf("=") + 1).trim();   
                            return valueString;   
                        }   
                    }   
                }   
  
            }   
        } catch (Exception e)   
        {   
            // TODO: handle exception   
  
        } finally  
        {   
            bufferedReader.close();   
        }   
        return defaultValue;   
    }   
  
    /**  
     * 修改ini配置文档中变量的值  
     *   
     * @param file  
     *            配置文档的路径  
     * @param section  
     *            要修改的变量所在段名称  
     * @param variable  
     *            要修改的变量名称  
     * @param value  
     *            变量的新值  
     * @throws IOException  
     *             抛出文档操作可能出现的io异常  
     */  
    public static boolean setProfileString(String file, String section, String variable, String value)   
            throws IOException   
    {   
        String fileContent, allLine;   
        BufferedReader bufferedReader = new BufferedReader(new FileReader(file));   
        boolean isInSection = false;   
        fileContent = "";   
        try  
        {   
            while ((allLine = bufferedReader.readLine()) != null)   
            {   
                allLine = allLine.trim();   
                Pattern p;   
                Matcher m, m2;   
                p = Pattern.compile("\\[\\s*" + section + "\\s*\\]");   
                Pattern p2 = Pattern.compile("\\[.*\\]");   
                m = p.matcher((allLine));   
                m2 = p2.matcher((allLine));   
                if (m2.find())   
                {   
                    if (m.find())   
                    {   
                        isInSection = true;   
                    } else  
                    {   
                        isInSection = false;   
                    }   
                }   
                if (isInSection == true)   
                {   
                    String[] strArray = allLine.split("=");   
                    if (allLine.indexOf("=") > 0)   
                    {   
                        String valueString = strArray[0].trim();   
                        if (valueString.equalsIgnoreCase(variable))   
                        {   
                            String newLine = valueString + "=" + value;   
                            fileContent += "    " + newLine + RN;   
                        } else  
                        {   
                            fileContent += "    " + allLine + RN;   
                        }   
                    } else  
                    {   
                        fileContent += allLine + RN;   
                    }   
                } else  
                {   
                    if (allLine.indexOf("=") > 0)   
                    {   
                        fileContent += "    " + allLine + RN;   
                    } else  
                    {   
                        fileContent += allLine + RN;   
                    }   
                }   
            }   
            // System.out.println(fileContent);   
            BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(file, false));   
            bufferedWriter.write(fileContent);   
            bufferedWriter.flush();   
            bufferedWriter.close();   
            return true;   
        } 
        catch (Exception e){   
            e.printStackTrace();   
        } finally {   
            bufferedReader.close();   
        }   
        return false;   
    }   
}