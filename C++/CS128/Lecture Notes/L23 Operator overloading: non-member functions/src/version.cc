#include "version.hpp"

Version::Version(int major, int minor, int patch) : major_(major), minor_(minor), patch_(patch) {
    if(major_ < 0)
        major_ = kMinComponent;
    if(minor_ < 0)
        minor_ = kMinComponent;
    if(patch_ < 0)
        patch_ = kMinComponent;
}

int Version::GetMajor() const{
    return major_;
}

int Version::GetMinor() const{
    return minor_;
}

int Version::GetPatch() const{
    return patch_;
}

bool operator==(const Version& lhs, const Version& rhs){
    return lhs.GetMajor() == rhs.GetMajor() && lhs.GetMinor() == rhs.GetMinor() && lhs.GetPatch() == rhs.GetPatch();
}

bool operator<(const Version& lhs, const Version& rhs){
    return lhs.GetMajor() < rhs.GetMajor() || (lhs.GetMajor() == rhs.GetMajor() && lhs.GetMinor() < rhs.GetMinor()) || (lhs.GetMajor() == rhs.GetMajor() && lhs.GetMinor() == rhs.GetMinor() && lhs.GetPatch() < rhs.GetPatch());
}

std::ostream& operator<<(std::ostream& os, const Version& version){
    os << version.GetMajor() << "." << version.GetMinor() << "." << version.GetPatch();
    return os;
}
