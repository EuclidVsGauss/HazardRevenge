# Makefile for building HazardRevenge across platforms

APP_NAME := HazardRevenge

# ---------- Build directories ----------
IOS_BUILD_DIR   := build-ios
MAC_BUILD_DIR   := build-mac
WIN_BUILD_DIR   := build-win
LINUX_BUILD_DIR := build-linux

IOS_CONFIG := Release
IOS_APP    := $(IOS_BUILD_DIR)/$(IOS_CONFIG)/$(APP_NAME).app
IOS_IPA    := /tmp/$(APP_NAME).ipa

# ---------- iOS assets ----------
IOS_ASSETS_DIR      := ios/assets
IOS_REQUIRED_ASSETS := $(IOS_ASSETS_DIR)/hazard.pak $(IOS_ASSETS_DIR)/music.pak $(IOS_ASSETS_DIR)/visual.pak
IOS_DUMMY_ASSET     := $(IOS_ASSETS_DIR)/hazard.sav

.DEFAULT_GOAL := help

.PHONY: help ios macos windows linux \
        ios-configure ios-build ios-sign ios-package ios-check-assets \
        configure build sign package \
        clean clean-ios clean-macos clean-windows clean-linux

# ---------- Help (default target) ----------
help:
	@echo "Available targets:"
	@echo "  ios        Build the iOS .ipa (drives configure/build/sign/package)"
	@echo "  macos      Build for macOS"
	@echo "  windows    Build for Windows (Visual Studio 2022; run on Windows)"
	@echo "  linux      Build for Linux"
	@echo "  clean      Remove all build artifacts"
	@echo "             (per-platform: clean-ios, clean-macos, clean-windows, clean-linux)"
	@echo "  help       Show this message (default)"

# ================= iOS =================
ios: ios-package

ios-check-assets:
	@for f in $(IOS_REQUIRED_ASSETS); do \
		if [ ! -f "$$f" ]; then \
			echo "Error: required asset '$$f' is missing." >&2; \
			exit 1; \
		fi; \
	done
	@if [ ! -f "$(IOS_DUMMY_ASSET)" ]; then \
		echo "Creating $(IOS_DUMMY_ASSET) (316176 zero bytes)"; \
		dd if=/dev/zero of="$(IOS_DUMMY_ASSET)" bs=316176 count=1 status=none; \
	fi

ios-configure: ios-check-assets
	cmake -S . -B $(IOS_BUILD_DIR) -G Xcode \
		-DCMAKE_SYSTEM_NAME=iOS \
		-DCMAKE_OSX_ARCHITECTURES=arm64 \
		-DCMAKE_OSX_SYSROOT=iphoneos \
		-DCMAKE_OSX_DEPLOYMENT_TARGET=15.0 \
		-DSDL_MAJOR=3 \
		-DSDL_STATIC=ON \
		-DSDL_SHARED=OFF

ios-build: ios-configure
	cmake --build $(IOS_BUILD_DIR) --config $(IOS_CONFIG)

ios-sign: ios-build
	codesign --force --sign - --generate-entitlement-der "$(IOS_APP)"

ios-package: ios-sign
	@STAGE=$$(mktemp -d) && \
		mkdir -p "$$STAGE/Payload" && \
		ditto "$(IOS_APP)" "$$STAGE/Payload/$(APP_NAME).app" && \
		( cd "$$STAGE" && zip -qry $(IOS_IPA) Payload ) && \
		rm -rf "$$STAGE" && \
		echo "Built $(IOS_IPA)"

# Backwards-compatible aliases for the old iOS-only targets
configure: ios-configure
build:     ios-build
sign:      ios-sign
package:   ios-package

# ================= macOS =================
macos:
	cmake -S . -B $(MAC_BUILD_DIR) -DCMAKE_BUILD_TYPE=Release -DSDL_MAJOR=3
	cmake --build $(MAC_BUILD_DIR) --parallel

# ================= Windows =================
windows:
	cmake -S . -B $(WIN_BUILD_DIR) -G "Visual Studio 17 2022" -A x64
	cmake --build $(WIN_BUILD_DIR) --config Release

# ================= Linux =================
linux:
	cmake -S . -B $(LINUX_BUILD_DIR) -DCMAKE_BUILD_TYPE=Release -DSDL_MAJOR=3
	cmake --build $(LINUX_BUILD_DIR) --parallel

# ================= Cleanup =================
clean-ios:
	rm -rf $(IOS_BUILD_DIR) $(IOS_IPA)

clean-macos:
	rm -rf $(MAC_BUILD_DIR)

clean-windows:
	rm -rf $(WIN_BUILD_DIR)

clean-linux:
	rm -rf $(LINUX_BUILD_DIR)

clean: clean-ios clean-macos clean-windows clean-linux