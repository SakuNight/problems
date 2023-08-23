import { readFile } from 'fs/promises'
import { execSync } from 'child_process'
import { platform, cwd } from 'process'
import path from 'path';

const build_dir = 'build';
const executable_suffix = platform == 'win32' ? '.exe' : ''

let case_count = 0;

async function work() {
    while (true) {
        ++case_count;
        console.log("Case #" + case_count);

        console.log("Running gen" + executable_suffix);
        execSync("\"" + path.join(cwd(), build_dir, 'gen' + executable_suffix) + "\"", {
            cwd: path.join(cwd(), build_dir),
            timeout: 10000
        });

        console.log("Running bf" + executable_suffix);
        execSync("\"" + path.join(cwd(), build_dir, 'bf' + executable_suffix) + "\"", {
            cwd: path.join(cwd(), build_dir),
            timeout: 30000
        });

        console.log("Running std" + executable_suffix);
        execSync("\"" + path.join(cwd(), build_dir, 'std' + executable_suffix) + "\"", {
            cwd: path.join(cwd(), build_dir),
            timeout: 1000
        });

        const bf_output = await readFile(path.join('build', 'bf.txt'))
        const std_output = await readFile(path.join('build', 'std.txt'))

        if (!bf_output.equals(std_output)) {
            console.log("Test Failed!!")
            console.log("in.txt:")
            const in_txt = await readFile(path.join('build', 'in.txt'))
            console.log(String(in_txt))
            return
        }
    }
}

work()