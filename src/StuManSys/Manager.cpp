#include "Manager.h"
#include "public_fun.h"


bool compare(Student a, Student b)
{
    return a._score > b._score;
}

void save_data_to_txt(std::vector<Student> stus)
{
    char lines[64] = { 0 };
    FILE *fp = nullptr;
    fopen_s(&fp, "student.txt", "w+");
    for (size_t i = 0; i < stus.size();i++)
    {
        memset(lines, 0, sizeof(lines));
        sprintf_s(lines, "%d %s %s %d \n", stus[i]._id, wctoch(stus[i]._name), wctoch(stus[i]._class), stus[i]._score);
        fwrite(lines, sizeof(char), strlen(lines), fp);
    }
    fclose(fp);
}

std::vector<Student> save_data_to_txt(const char* file)
{
    std::vector<Student> students;
    students.clear();
    char line[1024];
    FILE * fp = nullptr;
    const char *filepath = file;
    fopen_s(&fp, filepath, "r");
    if (fp) {
        while (!feof(fp)) {
            memset(line, 0, sizeof(line));
            Student stu;
            char * retch = NULL;
            if ((fgets(line, sizeof(line), fp) == NULL) || line[0] == '\n')
            {
                continue;
            }
            char *tmp;
            const char* s = " ";
            int  i = 0;
            // 使用strtok函数拆分字符串
            tmp = strtok(line, s);
            // 遍历并打印每个子字符串
            while (tmp != NULL) {
                if (i == 0)
                {
                    stu._id = atoi(tmp);
                }
                else if (i == 1)
                {
                    swprintf_s(stu._name, L"%s", chtowc(tmp));
                }
                else if (i == 2)
                {
                    swprintf_s(stu._class, L"%s", chtowc(tmp));
                }
                else
                {
                    stu._score = atoi(tmp);
                }
                printf(" %s\n", tmp);
                tmp = strtok(NULL, s);
                i++;
            }
            students.push_back(stu);
        }
        fclose(fp);    
    }
    else {
        printf("open file: %s error !\n", filepath);
    }
    return students;
}


Manager::Manager()
{
    m_students.clear();
}

Manager::~Manager()
{

}

bool Manager::read(const std::string& fileName)
{
    m_students.clear();
    // 以二进制读取模式打开文件
    std::ifstream file(fileName, std::ios::in | std::ios::binary);
    if (!file)
    {
        return false;
    }
    // 读取数据
    Student data = {};
    while (file.read((char*)&data, sizeof(Student)))
    {
        m_students.push_back(data);
    }
    file.close();

    return true;
}

void Manager::write(const std::string& fileName) const
{
    // 以二进制写入模式打开文件
    std::ofstream file(fileName, std::ios::out | std::ios::binary);

    // 写入数据
    for (size_t i = 0; i < m_students.size(); i++)
    {
        file.write((const char*)&m_students[i], sizeof(Student));
    }

    file.close();
}

void Manager::addStudent(const Student& student)
{
    m_students.push_back(student);
}

void Manager::sortById()
{
    std::sort(m_students.begin(), m_students.end());
}

void Manager::sortByScore()
{
    std::sort(m_students.begin(), m_students.end(), compare);
}

const Student& Manager::getStudent(int index) const
{
    return m_students[index];
}

void Manager::setStudent(int index, const Student& student)
{
    m_students[index] = student;
}

void Manager::deleteStudent(int index)
{
    m_students.erase(m_students.begin() + index);
}

int Manager::size() const
{
    return (int)m_students.size();
}

int Manager::search(const wchar_t* searchTerms) const
{
    std::vector<Student>::const_iterator iter;
    iter = std::find(m_students.begin(), m_students.end(), searchTerms);
    if (iter != m_students.end())
    {
        // 搜索成功，返回索引
        return (int)(iter - m_students.begin());
    }
    else
    {
        // 搜索失败，返回 -1 表示错误
        return -1;
    }
}

int Manager::search(int id) const
{
    std::vector<Student>::const_iterator iter;
    iter = std::find(m_students.begin(), m_students.end(), id);
    if (iter != m_students.end())
    {
        // 搜索成功，返回索引
        return (int)(iter - m_students.begin());
    }
    else
    {
        // 搜索失败，返回 -1 表示错误
        return -1;
    }
}

void Manager::clear()
{
    m_students.clear();
}


void Manager::update()
{

    char pathTmp[256] = { 0 };
    std::string filePath = "";
    get_parent_directory(pathTmp);
    filePath = pathTmp;
    filePath += std::string("/data/StuManSys/Students.txt");

    m_students.clear();
    std::vector<Student> vecs = save_data_to_txt(filePath.c_str());
    std::vector<Student>::iterator itor = vecs.begin();
    for (; itor != vecs.end(); itor++)
    {
        Student su;
        su._id = itor->_id;
        std::wcscpy(su._name, itor->_name);
        std::wcscpy(su._class, itor->_class);
        su._score = itor->_score;
        m_students.push_back(su);
    }
}


