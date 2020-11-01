/*如果长度不同,返回false,维护一个数组,对s中字符正计数,对t中字符负计数,时间复杂度O(n),空间复杂度O(1)
*https://leetcode-cn.com/problems/valid-anagram/
*/
bool isAnagram(char * s, char * t){
    int n = strlen(s);
    int m = strlen(t);
    if(n != m) return false;
    int a[26] = {0};
    for (int i = 0; i < n; i++) {
        a[s[i]-'a']++;
        a[t[i]-'a']--;
    }
    for (int i = 0; i < 26; i++) {
        if(a[i]!=0) return false;
    }
    return true;
}
