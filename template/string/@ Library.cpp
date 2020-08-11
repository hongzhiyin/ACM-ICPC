void trim(string &str) {
    string space("\f\v\r\t\n ");
    str.erase(0,str.find_first_not_of(space));
    str.erase(str.find_last_not_of(space) + 1);
}