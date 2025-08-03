local copy = function (target)
        import("core.project.config")
        os.cp("$(scriptdir)/resources", "$(builddir)/$(host)/$(arch)/$(mode)")
        print("资源:%s","$(builddir)/$(host)/$(arch)/$(mode)")
    end

target("text_font_filters", {kind = "binary", files = "text_font_filters.cpp",after_build = copy})
target("text_font_loading", {kind = "binary", files = "text_font_loading.cpp",after_build = copy})
target("text_font_spritefont", {kind = "binary", files = "text_font_spritefont.cpp",after_build = copy})
target("text_raylib_fonts", {kind = "binary", files = "text_raylib_fonts.cpp",after_build = copy})
