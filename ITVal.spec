#
# spec file for package ITVal (Version 1.0)
#

BuildRequires: aaa_base acl attr bash bzip2 coreutils db devs diffutils filesystem fillup glibc gdbm grep insserv libacl libattr libgcc libnscd libselinux libxcrypt m4 ncurses pam permissions popt pwdutils readline sed tar zlib rpm gcc-c++ libstdc++-devel autoconf automake binutils bison flex gcc glibc-devel glibc-locale groff gzip info klogd less libstdc++ libtool make man module-init-tools net-tools netcfg pam-modules patch perl procinfo procps psmisc rcs syslogd e2fsprogs gettext sysvinit tcpd texinfo unzip vim zlib-devel libzio

Summary: Testing and Validation Tool for Iptables
Name: ITVal
Version: 1.0
Release: 0
URL: http://itval.sourceforge.net
Source0: %{name}-%{version}.tar.bz2
License: GPL
Group: Productivity/Security
BuildRoot: %{_tmppath}/%{name}-%{version}-build

%description

ITVal is a tool for iptables configuration analysis.  It can be used to: detect
unprotected ports and hosts, determine whether certain services are incorrectly
blocked by the firewall, validate changes to the firewall policy, or generate
an equivalence class abstraction of the firewall policy.

%prep
%setup -q

%build
./configure --prefix ${RPM_BUILD_ROOT}/usr --libdir ${RPM_BUILD_ROOT}/%{_libdir}
make

%install 
make install

%files
%defattr(-,root,root)
%doc README LICENSE RELEASE AUTHORS COPYING INSTALL 
/usr/bin/ITVal
%{_libdir}/libFDDL.a
%{_libdir}/libFDDL.la
%{_libdir}/libFDDL.so.0.0.0
%{_libdir}/libFDDL.so.0
%{_libdir}/libFDDL.so
/usr/include/ITVal/mdd.h
/usr/include/ITVal/mddtypes.h
/usr/include/ITVal/caches.h
/usr/include/ITVal/dynarray.h
/usr/include/ITVal/uniquetable.h
/usr/man/mann/ITVal.n.gz

%changelog

* Fri Feb 2 2007 Robert Marmorstein
	- Packaged as an RPM for SuSE 10.0
