Name:		femtoconf
Version:	1
Release:	1%{?dist}
Summary:	Even smaller configuration file parser library

Group:		System Environment/Libraries
License:	MIT
URL:		http://github.com/Mordae/femtoconf/
Source0:	%{name}-%{version}.tar.gz

BuildRoot:      %_tmppath/%name-%version-%release-buildroot

%description
Library for parsing extremely simple key/value configuration files.


%package devel
Summary:	Development files for the femtoconf library.
Group:		Development/Libraries

%description devel
Files required to build programs linking to the femtoconf library.

%prep
%setup -q


%build
make %{?_smp_mflags}


%install
make install DESTDIR=$RPM_BUILD_ROOT


%clean
rm -rf "$RPM_BUILD_ROOT"


%files
%{_libdir}/libfemtoconf.so.*

%files devel
%{_libdir}/libfemtoconf.so
%{_includedir}/femtoconf.h


%changelog

