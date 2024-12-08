local copy = function (target)
        import("core.project.config")
        os.cp("$(scriptdir)/resources", "$(buildir)/$(host)/$(arch)/$(mode)")
        print("资源:%s","$(buildir)/$(host)/$(arch)/$(mode)")
    end

target("models_billboard", {kind = "binary", files = "models_billboard.cpp",after_build = copy})
target("models_first_person_maze", {kind = "binary", files = "models_first_person_maze.cpp",after_build = copy})
 