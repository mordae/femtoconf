Name:		libfconf
Version:	1
Release:	1%{?dist}
Summary:	Even smaller configuration file parser library

Group:		Development/Other
License:	MIT
URL:		http://github.com/Mordae/libfconf/
Source0:	%{name}-%{version}.tar.gz

BuildRoot:      %_tmppath/%name-%version-%release-buildroot

%description
Library for parsing extremely simple key/value configuration files.

%prep
%setup -q


%build
make %{?_smp_mflags}


%install
make install DESTDIR=$RPM_BUILD_ROOT


%clean
rm -rf "$RPM_BUILD_ROOT"


%files
%{_includedir}/*
%{_libdir}/*


%changelog

