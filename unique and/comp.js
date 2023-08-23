import { readFile } from 'fs/promises'
import { execSync } from 'child_process'
import { platform, cwd } from 'process'
import 'path'
import path from 'path';

const build_dir = 'build';
const executable_suffix = platform == 'win32' ? '.exe' : ''

let case_count = 0;

async function wait_close(process) {
    return new Promise((resolve, reject) => {
        process.on("close", (code) => {
            resolve(code)
        })
        process.on("error", () => {
            resolve(-1)
        })
    })
}

async function work() {
    while (true) {
        ++case_count;
        console.log("Case #" + case_count);

        console.log("Running makedata" + executable_suffix);
        execSync("\"" + path.join(cwd(), build_dir, 'makedata' + executable_suffix) + "\"", {
            cwd: path.join(cwd(), build_dir),
            timeout: 10000
        });

        console.log("Running brute_force" + executable_suffix);
        execSync("\"" + path.join(cwd(), build_dir, 'brute_force' + executable_suffix) + "\"", {
            cwd: path.join(cwd(), build_dir),
            timeout: 30000
        });

        console.log("Running std" + executable_suffix);
        execSync("\"" + path.join(cwd(), build_dir, 'std' + executable_suffix) + "\"", {
            cwd: path.join(cwd(), build_dir),
            timeout: 1000
        });

        // const sol_status = await wait_close(sol_process)
        // const std_status = await wait_close(std_process)

        // if (sol_status < 0) {
        //     console.log("brute_force execution error")
        // }
        // if (std_status < 0) {
        //     console.log("std execution error")
        // }

        // if (sol_status > 0) {
        //     console.log("brute_force return non-zero value")
        // }
        // if (std_status > 0) {
        //     console.log("std return non-zero value")
        // }

        // if (sol_status !== 0 || std_status !== 0) {
        //     return
        // }

        const sol_output = await readFile(path.join('build', 'sol.txt'))
        const std_output = await readFile(path.join('build', 'std.txt'))

        if (!sol_output.equals(std_output)) {
            console.log("Test Failed!!")
            console.log("in.txt:")
            const in_txt = await readFile(path.join('build', 'in.txt'))
            console.log(String(in_txt))
            return
        }
    }
}

work()