include $(TOPDIR)/rules.mk

PKG_NAME:=libupnplog
PKG_RELEASE:=1
PKG_VERSION:=1.0.0


include $(INCLUDE_DIR)/package.mk

define Package/libupnplog
	DEPENDS:=+libsqlite3
	SECTION:=libs
	CATEGORY:=Libraries
	TITLE:=libupnplog
endef

define Package/libupnplog/description
	Library for miniupnpd daemon to log denied addresses
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/lib $(1)/usr/include
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/libupnplog.so $(1)/usr/lib
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/log_denied_addr.h $(1)/usr/include/
endef

define Package/libupnplog/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/libupnplog.so $(1)/usr/lib
	$(INSTALL_BIN) ./files/upnp_logs $(1)/usr/bin
endef

$(eval $(call BuildPackage,libupnplog))