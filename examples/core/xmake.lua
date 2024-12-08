local copy = function (target)
        import("core.project.config")
        os.cp("$(scriptdir)/resources", "$(buildir)/$(host)/$(arch)/$(mode)")
        print("资源:%s","$(buildir)/$(host)/$(arch)/$(mode)")
    end

target("core_basic_window_web", {kind = "binary", files = "core_basic_window_web.cpp",after_build = copy})
target("core_basic_window", {kind = "binary", files = "core_basic_window.cpp",after_build = copy})
target("core_drop_files", {kind = "binary", files = "core_drop_files.cpp",after_build = copy})
target("core_input_mouse", {kind = "binary", files = "core_input_mouse.cpp",after_build = copy})
target("core_loading_thread", {kind = "binary", files = "core_loading_thread.cpp",after_build = copy})
target("core_random_values", {kind = "binary", files = "core_random_values.cpp",after_build = copy})
target("core_window_letterbox", {kind = "binary", files = "core_window_letterbox.cpp",after_build = copy})
target("core_world_screen", {kind = "binary", files = "core_world_screen.cpp",after_build = copy})
